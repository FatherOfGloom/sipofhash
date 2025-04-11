# $source = "C:\Source\file.txt"
# $dest = "C:\Destination\"

param(
    [string]$source = "hash_test.out",
    [string]$dest = "test_data\"
)

New-Item -ItemType Directory -Path $dest -Force | Out-Null

$name = [System.IO.Path]::GetFileNameWithoutExtension($source)
$ext = [System.IO.Path]::GetExtension($source)
$counter = 0
$newname = "$name$ext"

while (Test-Path "$dest$newname") {
    $lastname = $newname
    $newname = "$name($counter)$ext"
    $counter++
}

if (($counter - 1) -ge 0) {
    Write-Host "Mover: $lastname already exists."
}

Copy-Item $source "$dest$newname"

Write-Host "Mover: $newname created."