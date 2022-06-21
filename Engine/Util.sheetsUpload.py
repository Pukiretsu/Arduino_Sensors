import pygsheets as psh
import pandas as pd

# We make an auth entrypoint
_Service = psh.authorize(service_file="Engine\Keys\PybotKey.json")


df = pd.DataFrame()

df['Esto fue'] = ['Enviado', 'desde', 'python', '😎']

sH = _Service.open("GoogleSheetTest")

workSheet = sH[0]

workSheet.set_dataframe(df, (1,1)) # Column - Row







