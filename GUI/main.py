from kivymd.app import MDApp
from kivy.lang import Builder

kivyFile = open("GUI\layout.kv","r")
layout = kivyFile.read()
kivyFile.close()

class Main(MDApp):

    def build(self):
        self.icon = "GUI/assets/appico.png"
        return Builder.load_string(layout)

    def text_Action(self):
        label = self.root.ids.Texto
        label.text = "Pulsaste el boton."
Main().run()