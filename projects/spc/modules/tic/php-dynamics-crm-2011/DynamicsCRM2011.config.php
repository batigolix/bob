<?php
/* Basic configuation details */
// Discovery Service URI -> Get this from the Customizations / Developer Resources section of the Microsoft Dynamics CRM 2011 application
//
$discoveryServiceURI = 'https://disco.crm4.dynamics.com/XRMServices/2011/Discovery.svc';
//$discoveryServiceURI = 'https://<your.domain.name>/XRMServices/2011/Discovery.svc';
// Organization Unique Name -> Get this from the Customizations / Developer Resources section of the Microsoft Dynamics CRM 2011 application
$organizationUniqueName = 'dgconnectdemo';
// Username & Password - Note that despite the text on the ADFS site, the Domain is NOT required!
$loginUsername = ' Albert@dgconnectdemo.onmicrosoft.com';
$loginPassword = ' Zupo4754';

/* Example data used in the Demos */
$demoCaseNumber = 'CAS-XXXXX-XXXX';
$demoContactEmail = 'bdoesborg@gmail.com';
?>