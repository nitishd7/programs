param(
    [Parameter(Mandatory=$True, Position=1)]
    [String]$SubscriptionName,

    [Parameter(Position=2)]
    [Boolean]$ForVirtualMachines=[Boolean]$True,

    [Parameter(Position=3)]
    [Boolean]$ForWebWorkerRoles=[Boolean]$True,

    [Parameter(Position=4)]
    [String]$Series
)

Function Invoke-TernaryOperator{
    param(
        [Parameter(Mandatory=$True, Position=1)]
        [Boolean]$evaluator,

        [Parameter(Mandatory=$True, Position=2)]
        [scriptBlock]$TrueScriptBlock,

        [Parameter(Mandatory=$True, Position=3)]
        [scriptBlock]$FalseScriptBlock
    )

    if($evaluator){
        &$TrueScriptBlock
    }
    else{
        &$FalseScriptBlock
    }
}


try{
    ### Check if the Azure module, else force install
    if(Get-Module -ListAvailable -Name Azure){
        Write-Host "Azure module is installed"
    }
    else {Install-Module  Azure -Force}
    Write-Progress "Azure Module Exists"

    $env:PSModulePath += ";C:\Program Files (x86)\Microsoft SDKs\Windows Azure\PowerShell\"
    Import-Module Azure
    Write-Progress "Modules Imported"

    Add-AzureAccount
    Set-Alias ?: Invoke-TernaryOperator

    $x = 0
    $x += ?: ($ForVirtualMachines -eq $True) {[int]2} {[int]0}
    $x += ?: ($ForWebWorkerRoles -eq $True) {[int]1} {[int]0}

    switch ($x) {
        1{
                if($Series -eq ""){
                    Get-AzureRoleSize | Where-Object {$_.SupportedByWebWorkerRoles -eq $True} | Format-Table InstanceSize, Cores, MemoryInMb, MaxDataDiskCount, WebWorkerResourceDiskSizeInMb, VirtualMachineResourceDiskSizeInMb
                }
                else{
                    Get-AzureRoleSize | Where-Object {$_.SupportedByWebWorkerRoles -eq $True} | Where-Object {$_.InstanceSize -like $Series} | Format-Table InstanceSize, Cores, MemoryInMb, MaxDataDiskCount, WebWorkerResourceDiskSizeInMb, VirtualMachineResourceDiskSizeInMb, SupportedByWebWorkerRoles, SupportedByVirtualMachines
                }
        }
        2{
                if($Series -eq ""){
                    Get-AzureRoleSize | Where-Object {$_.SupportedByVirtualMachines -eq $True} | Format-Table InstanceSize, Cores, MemoryInMb, MaxDataDiskCount, WebWorkerResourceDiskSizeInMb, VirtualMachineResourceDiskSizeInMb
                }
                else{
                    Get-AzureRoleSize | Where-Object {$_.SupportedByVirtualMachines -eq $True} | Where-Object {$_.InstanceSize -like $Series} | Format-Table InstanceSize, Cores, MemoryInMb, MaxDataDiskCount, WebWorkerResourceDiskSizeInMb, VirtualMachineResourceDiskSizeInMb, SupportedByWebWorkerRoles, SupportedByVirtualMachines
                }
        }
        3{
            if($Series -eq "") {
                Get-AzureRoleSize | Format-Table InstanceSize, Cores, MemoryInMb, MaxDataDiskCount, WebWorkerResourceDiskSizeInMb, VirtualMachineResourceDiskSizeInMb, SupportedByWebWorkerRoles, SupportedByVirtualMachines
            }
            else{
                $matchValue =  "*$Series*"
                Get-AzureRoleSize | Where-Object {$_.InstanceSize -like $matchValue} | Format-Table InstanceSize, Cores, MemoryInMb, MaxDataDiskCount, WebWorkerResourceDiskSizeInMb, VirtualMachineResourceDiskSizeInMb, SupportedByWebWorkerRoles, SupportedByVirtualMachines
            }
        }
        Default {Write-Host $x}
    }
    throw $_.Exception
}
catch [System.Exception] {
    Write-Host $_.Exception
} 
