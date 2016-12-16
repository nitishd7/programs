############################################################
##   Author: Nitish Nandan Devavarapu                     ##
##   CreatedDate: 2016-11-16                              ##
##   Parameters: EnvironmentName, ServiceName             ##
##   Version:                                             ##
##   1.0.0   First Implementation                         ##
############################################################
param(
    [Parameter(Mandatory=$True,Position=1)]
    [String]$EnvironmentName,

    [Parameter(Position=2)]
    [String]$ServiceName
)

### Check if the Azure module, else force install
if(Get-Module -ListAvailable -Name Azure){
    Write-Host "Azure module is installed"
}
else {Install-Module  Azure -Force}
Write-Progress "Azure Module Exists"

### Check if the AzureRM module, else force install
if(Get-Module -ListAvailable -Name AzureRM){
    Write-Host "Azure RM module is installed"
}
else {Install-Module AzureRM -Force}
Write-Progress "AzureRM Module Exists"

$env:PSModulePath += ";C:\Program Files (x86)\Microsoft SDKs\Windows Azure\PowerShell\"
Import-Module Azure
Import-Module AzureRM 
Write-Progress "Modules Imported"

#try {
    Add-AzureAccount
    Select-AzureSubscription -SubscriptionName "EC-MBS-D1"
    
   # Login-AzureRmAccount
   # Get-AzureRmSubscription
    Get-AzureService | Format-List ServiceName
    Get-AzureServiceExtension  
#}
#catch [System.Exception] {
    
#}

