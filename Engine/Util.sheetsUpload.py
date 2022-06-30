import pygsheets as psh

# We make an auth entrypoint
values = {'T superficial': '',
          'T interna': '',
          'T alrededores': '',
          'Tiempo': ''}

key = list(values.keys())


# Configuramos la hoja de google sheets
_Service = psh.authorize(service_file="Engine\Keys\PybotKey.json")
sheets = _Service.open("PruebaPybot")
hoja = "lol"
try:
    worksheet = sheets.worksheet_by_title(hoja)
except:
    sheets.add_worksheet(hoja)
    worksheet = sheets.worksheet_by_title(hoja)
    




