# Create deps directory if it doesn't exist
if (-not (Test-Path "deps")) {
    New-Item -ItemType Directory -Path "deps"
}

# Download and extract libcurl
$curlUrl = "https://curl.se/windows/dl-8.6.0_3/curl-8.6.0_3-win64-mingw.zip"
$curlZip = "deps/curl.zip"
$curlExtractPath = "deps/curl"

Write-Host "Downloading libcurl..."
Invoke-WebRequest -Uri $curlUrl -OutFile $curlZip

Write-Host "Extracting libcurl..."
Expand-Archive -Path $curlZip -DestinationPath $curlExtractPath -Force
Remove-Item $curlZip

# Download and extract jsoncpp
$jsoncppUrl = "https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.5.zip"
$jsoncppZip = "deps/jsoncpp.zip"
$jsoncppExtractPath = "deps/jsoncpp"

Write-Host "Downloading jsoncpp..."
Invoke-WebRequest -Uri $jsoncppUrl -OutFile $jsoncppZip

Write-Host "Extracting jsoncpp..."
Expand-Archive -Path $jsoncppZip -DestinationPath $jsoncppExtractPath -Force
Remove-Item $jsoncppZip

Write-Host "Dependencies downloaded and extracted successfully!" 