<?php
/**
*   Dynamics CRM 2013 Online PHP Soap Class
*   Connects to Dynamics CRM Online via SOAP webservice using Office365 Authentication
*
*   @param int  $debug      0 = Off, 1 = On
 * 
 * http://www.hashtagcrm.com/?p=17
*
*/
class dynamicsClient
{
 
  function dynamicsClient() {
    $this->__construct();
  }
 
  function __construct($debug=0) {
 
//    Here are credentials of a user you can use for your tests:
//https://dgconnectdemo.crm4.dynamics.com/main.aspx#
//Albert@dgconnectdemo.onmicrosoft.com
//Zupo4754
//        
    
    $this->email    = 'Albert@dgconnectdemo.onmicrosoft.com';
    $this->password = 'Zupo4754';
    $this->orgname  = 'dgconnectdemo';
 
    $this->dynamicsRegion = 'crmna';
 
    $this->messageid = $this->create_guid();
 
    $this->orgPoint    = "/XRMServices/2011/Organization.svc";
    $this->dynamicsUrl = $this->orgname.'.api.crm.dynamics.com';
    $this->debug       =  $debug;
 
    $this->securityToken0 = '';
    $this->securityToken1 = '';
    $this->keyIdentifier  = '';
    $this->_lastRequest   = '';
    $this->_lastResponse  = '';
    $this->_error         = '';
 
    $this->currentTime = '';
    $this->nextDayTime = '';
 
    $this->loginO365();
  }
 
  // ---- Add your own functions here as needed ----
  // ---- Use the SOAP Logger tool in the SDK to capture SOAP requests, then use them in your own functions here ----
 
  //Returns the Parent Account Name of the specified Contact
  public function sampleFunction($contactid){
 
    $getParentCustomer = '
                        <Retrieve xmlns="http://schemas.microsoft.com/xrm/2011/Contracts/Services" xmlns:i="http://www.w3.org/2001/XMLSchema-instance">
                          <entityName>contact</entityName>
                          <id>'.$contactid.'</id>
                          <columnSet xmlns:a="http://schemas.microsoft.com/xrm/2011/Contracts">
                            <a:AllColumns>false</a:AllColumns>
                            <a:Columns xmlns:b="http://schemas.microsoft.com/2003/10/Serialization/Arrays">
                              <b:string>parentcustomeridname</b:string>
                            </a:Columns>
                          </columnSet>
                        </Retrieve>';
 
    $getParentCustomerResult = $this->sendQuery($getParentCustomer, 'Retrieve');
 
    $responsedom = new DomDocument();
    $responsedom->loadXML($getParentCustomerResult);
    $KeyValuePairs = $responsedom->getElementsbyTagName("KeyValuePairOfstringanyType");
 
    foreach($KeyValuePairs as $results) {
      if ($results->childNodes->item(0)->nodeValue == "parentcustomeridname") {
        return $results->childNodes->item(1)->childNodes->item(0)->nodeValue;
      }
      else {
        return 'No Result';
      }
    }
  }
 
  // ---- Private functions ----
 
  /**
  * Logs into Office365
  *
  * @return true on success else error
  */
  private function loginO365() {
 
    $this->currentTime = substr(date("c"), 0, -6).'Z';
    $this->nextDayTime = substr(date("c", strtotime($this->currentTime.' +1 day')), 0, -6).'Z';
 
    // Get security tokens
    $response     = $this->getSecurityTokens();
    $responsedom  = new DomDocument();
    $responsedom->loadXML($response);
    $cipherValues = $responsedom->getElementsbyTagName("CipherValue");
 
    $this->securityToken0 =  $cipherValues->item(0)->textContent;
    $this->securityToken1 =  $cipherValues->item(1)->textContent;
    $this->keyIdentifier  =  $responsedom->getElementsbyTagName("KeyIdentifier")->item(0)->textContent;
 
    //Get the provided token created/expiry time from the authentication response
    $this->currentTime = $responsedom->getElementsbyTagName("Created")->item(1)->textContent;  //Should return the time the request was sent (server timezone, not local timezone)
    $this->nextDayTime = $responsedom->getElementsbyTagName("Expires")->item(1)->textContent;  //Should return request time +8 hours
 
    if (empty($this->keyIdentifier) || empty($this->securityToken0) || empty($this->securityToken1)) {
      $this->_error = "Authentication Error";
    }
    else {
      return true;
    }
  }
 
  /**
  * Makes the SOAP call
  *
  * @param  string $request    Soap method
  * @param  string $action     The type of action to be performed valid values: 'Create' 'Retrieve' 'RetrieveMultiple'
  *
  * @return result
  */
  private function sendQuery($request, $action){
 
    $xml = '<?xml version="1.0" encoding="utf-8" ?'. '>
    <s:Envelope xmlns:s="http://www.w3.org/2003/05/soap-envelope" xmlns:a="http://www.w3.org/2005/08/addressing" xmlns:u="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd">'.$this->getHeader($action).'<s:Body>'.$request.'</s:Body>
    </s:Envelope>';
 
    return $this->doCurl($this->orgPoint, $this->dynamicsUrl, "https://".$this->dynamicsUrl.$this->orgPoint, $xml);
  }
 
  /**
  * Generate Soap Header
  * Generates valid crm auth header
  *
  * @return soap header
  */
  private function getHeader($action) {
 
    // If we dont have any of the security tokens try to log in
    if (empty($this->keyIdentifier) || empty($this->securityToken0) || empty($this->securityToken1)){
      $this->loginO365();
    }
 
    $header = '
        <s:Header>
            <a:Action s:mustUnderstand="1">http://schemas.microsoft.com/xrm/2011/Contracts/Services/IOrganizationService/'.$action.'</a:Action>
            <a:MessageID>urn:uuid:'.$this->messageid.'</a:MessageID>
            <a:ReplyTo><a:Address>http://www.w3.org/2005/08/addressing/anonymous</a:Address></a:ReplyTo>
            <a:To s:mustUnderstand="1">https://'.$this->dynamicsUrl.'/XRMServices/2011/Organization.svc</a:To>
            <o:Security s:mustUnderstand="1" xmlns:o="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd">
            <u:Timestamp u:Id="_0">
                <u:Created>'.$this->currentTime.'</u:Created>
                <u:Expires>'.$this->nextDayTime.'</u:Expires>
            </u:Timestamp>
            <EncryptedData Id="Assertion0" Type="http://www.w3.org/2001/04/xmlenc#Element" xmlns="http://www.w3.org/2001/04/xmlenc#">
                <EncryptionMethod Algorithm="http://www.w3.org/2001/04/xmlenc#tripledes-cbc"></EncryptionMethod>
                <ds:KeyInfo xmlns:ds="http://www.w3.org/2000/09/xmldsig#">
                    <EncryptedKey>
                        <EncryptionMethod Algorithm="http://www.w3.org/2001/04/xmlenc#rsa-oaep-mgf1p"></EncryptionMethod>
                        <ds:KeyInfo Id="keyinfo">
                            <wsse:SecurityTokenReference xmlns:wsse="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd">
                                <wsse:KeyIdentifier EncodingType="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-soap-message-security-1.0#Base64Binary" ValueType="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-x509-token-profile-1.0#X509SubjectKeyIdentifier">'.$this->keyIdentifier.'</wsse:KeyIdentifier>
                            </wsse:SecurityTokenReference>
                        </ds:KeyInfo>
                        <CipherData>
                            <CipherValue>'.$this->securityToken0.'</CipherValue>
                        </CipherData>
                    </EncryptedKey>
                </ds:KeyInfo>
                <CipherData>
                    <CipherValue>'.$this->securityToken1.'</CipherValue>
                </CipherData>
            </EncryptedData>
            </o:Security>
        </s:Header>';
 
    return $header;
  }
 
  /**
  * Gets Security Tokens
  *
  * @return result
  */
  private function getSecurityTokens() {
 
    $securityTokenSoapTemplate = '<?xml version="1.0" encoding="utf-8" ?'. '>
        <s:Envelope xmlns:s="http://www.w3.org/2003/05/soap-envelope" xmlns:a="http://www.w3.org/2005/08/addressing" xmlns:u="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd">
            <s:Header>
                <a:Action s:mustUnderstand="1">http://schemas.xmlsoap.org/ws/2005/02/trust/RST/Issue</a:Action>
                <a:MessageID>urn:uuid:'.$this->messageid.'</a:MessageID>
                <a:ReplyTo><a:Address>http://www.w3.org/2005/08/addressing/anonymous</a:Address></a:ReplyTo>
                <a:To s:mustUnderstand="1">https://login.microsoftonline.com/RST2.srf</a:To>
                <o:Security s:mustUnderstand="1" xmlns:o="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd">
                    <u:Timestamp u:Id="_0">
                        <u:Created>'.$this->currentTime.'</u:Created>
                        <u:Expires>'.$this->nextDayTime.'</u:Expires>
                    </u:Timestamp>
                    <o:UsernameToken u:Id="user">
                        <o:Username>'.$this->email.'</o:Username>
                        <o:Password Type="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText">'.$this->password.'</o:Password>
                    </o:UsernameToken>
                </o:Security>
            </s:Header>
                <s:Body>
                    <t:RequestSecurityToken xmlns:t="http://schemas.xmlsoap.org/ws/2005/02/trust">
                        <wsp:AppliesTo xmlns:wsp="http://schemas.xmlsoap.org/ws/2004/09/policy">
                            <a:EndpointReference><a:Address>urn:'.$this->dynamicsRegion.':dynamics.com</a:Address></a:EndpointReference>
                        </wsp:AppliesTo>
                        <t:RequestType>http://schemas.xmlsoap.org/ws/2005/02/trust/Issue</t:RequestType>
                    </t:RequestSecurityToken>
                </s:Body>
            </s:Envelope>';
 
    return $this->doCurl("/RST2.srf", "login.microsoftonline.com", "https://login.microsoftonline.com/RST2.srf", $securityTokenSoapTemplate);
  }
 
  /**
  * Create microsoft-compatible GUID
  * @param  string $namespace optional namespace
  * @return MS GUID
  *
  * Modified from http://www.php.net/manual/en/function.uniqid.php#107512
  *
  */
  private function create_guid($namespace = '') {
    static $guid = '';
    $uid = uniqid("", true);
    $data = $namespace;
    $data .= $_SERVER['REQUEST_TIME'];
    $data .= $_SERVER['HTTP_USER_AGENT'];
    $data .= $_SERVER['REMOTE_ADDR'];
    $data .= $_SERVER['REMOTE_PORT'];
    $hash = strtoupper(hash('ripemd128', $uid . $guid . md5($data)));
    $guid = substr($hash,  0,  8) .
      '-' .
      substr($hash,  8,  4) .
      '-' .
      substr($hash, 12,  4) .
      '-' .
      substr($hash, 16,  4) .
      '-' .
      substr($hash, 20, 12);
    return $guid;
  }
 
  /**
  * Prints readable XML
  * @param  string $title  Title of the output
  * @param  string $output Content
  * @return formatted XML
  */
  function printXml($title,$output) {
    echo '<h1>'.$title.'</h1><pre>' . wordwrap(htmlspecialchars($output, ENT_QUOTES), 40, "<br />\n") . '</pre><br /><br />';
  }
 
  /**
  * Sends and recives SOAP messages via cURL
  * @param  string $postUrl  File to post to
  * @param  string $hostname Hostname
  * @param  string $soapUrl  URL to post to
  * @param  string $content  SOAP content
  * @return result
  */
  private function doCurl($postUrl, $hostname, $soapUrl, $content) {
 
    $headers = array(
                "POST ". $postUrl ." HTTP/1.1",
                "Host: " . $hostname,
                'Connection: Keep-Alive',
                "Content-type: application/soap+xml; charset=UTF-8",
                "Content-length: ".strlen($content),
    );
 
    $this->_lastRequest = $content;
    if ($this->debug == 1){ $this->printXml('REQUEST: ',$content); }
 
    $cURL = curl_init();
 
    curl_setopt($cURL, CURLOPT_URL, $soapUrl);
    curl_setopt($cURL, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($cURL, CURLOPT_TIMEOUT, 60);
    curl_setopt($cURL, CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($cURL, CURLOPT_FOLLOWLOCATION, TRUE);
    curl_setopt($cURL, CURLOPT_SSLVERSION , 3);
    curl_setopt($cURL, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_setopt($cURL, CURLOPT_HTTPHEADER, $headers);
    curl_setopt($cURL, CURLOPT_POST, 1);
    curl_setopt($cURL, CURLOPT_POSTFIELDS, $content);
 
    $response = curl_exec($cURL);
 
    curl_close($cURL);
 
    $this->_lastResponse = $response;
    if ($this->debug == 1) { $this->printXml('RESPONSE: ',$response); }
 
    return $response;
  }
}
?>