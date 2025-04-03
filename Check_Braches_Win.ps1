Get-ChildItem -Filter "*.c" | ForEach-Object {
    $archivo = $_.Name
    Write-Output "Procesando: $archivo"

    $contenido = Get-Content $_.FullName -Raw
    $apertura = ($contenido -split "{").Count - 1
    $cierre = ($contenido -split "}").Count - 1

    Write-Output "Llaves de apertura: $apertura"
    Write-Output "Llaves de cierre: $cierre"

    if ($apertura -ne $cierre) {
        Write-Output "El archivo '$archivo' tiene desbalance de llaves: $apertura '{' y $cierre '}'."
    } else {
        Write-Output "El archivo '$archivo' está bien balanceado."
    }
    Write-Output "----------------------------------"
}
