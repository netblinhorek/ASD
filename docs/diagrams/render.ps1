# Render Mermaid diagram to SVG and PNG using mermaid-cli (requires Node.js and @mermaid-js/mermaid-cli)
# Usage: powershell -NoProfile -ExecutionPolicy Bypass -File .\render.ps1

$root = Split-Path -Parent $PSScriptRoot
$input = Join-Path $root "tables_diagram.mmd"
$outSvg = Join-Path $root "tables_diagram.svg"
$outPng = Join-Path $root "tables_diagram.png"

Write-Host "Input: $input"

# Try to run npx mermaid-cli
$cmdSvg = "npx --yes @mermaid-js/mermaid-cli -i `"$input`" -o `"$outSvg`""
$cmdPng = "npx --yes @mermaid-js/mermaid-cli -i `"$input`" -o `"$outPng`""

Write-Host "Running: $cmdSvg"
$svgResult = & cmd /c $cmdSvg
Write-Host $svgResult

Write-Host "Running: $cmdPng"
$pngResult = & cmd /c $cmdPng
Write-Host $pngResult

Write-Host "Done. Generated files (if command succeeded):`n$outSvg`n$outPng"
