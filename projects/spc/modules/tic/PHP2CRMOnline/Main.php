<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

include_once "LiveIdManager.php";
include_once "EntityUtils.php";


$liveIDUseranme = "Albert@dgconnectdemo.onmicrosoft.com";
$liveIDPassword = "Zupo4754";

//Here are credentials of a user you can use for your tests:
//https://dgconnectdemo.crm4.dynamics.com/main.aspx#
//Albert@dgconnectdemo.onmicrosoft.com
//Zupo4754
////
//https://dgconnectdemo.api.crm4.dynamics.com/XRMServices/2011/Organization.svc
//Download WSDL

$organizationServiceURL = "https://dgconnectdemo.api.crm4.dynamics.com/XRMServices/2011/Organization.svcc";
$liveIDManager = new LiveIDManager();

$securityData = 
$liveIDManager->authenticateWithLiveID( $organizationServiceURL, $liveIDUseranme, $liveIDPassword );

//Print out the token received from WLID

if($securityData!=null && isset($securityData)){
    echo ("\nKey Identifier:" . $securityData->getKeyIdentifier());
    echo ("\nSecurity Token 1:" . $securityData->getSecurityToken0());
    echo ("\nSecurity Token 2:" . $securityData->getSecurityToken1());
}else{
    echo "Unable to authenticate LiveId.";
    return;
}
