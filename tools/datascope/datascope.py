# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '.\datascope.ui'
#
# Created by: PyQt5 UI code generator 5.10
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
import datascope_ui
from pyqtgraph import PlotWidget
import pyqtgraph as pg
import serial
import numpy as np

class MainWindow(datascope_ui.Ui_MainWindow,QtWidgets.QMainWindow):
    interval=30
    def __init__(self,parent=None):
        super(MainWindow,self).__init__(parent)
        self.setupUi(self)
        self.connectButton.clicked.connect(self.slotConnect)

        self.string=''
        self.lineNum=2
        self.data=np.array([[0.0]*400]*self.lineNum)

        self.plotView.showGrid(True,True)
        self.curve=self.plotView.plot()

        self.timer=QtCore.QTimer()
        self.timer.timeout.connect(self.update)


    def slotConnect(self):
        try:
            port=self.comEdit.text()
            baudrate=int(self.baudrateEdit.text())
            self.com=serial.Serial(port=port,baudrate=baudrate)
            if self.com.isOpen()==True:
                self.connectButton.setText("断开")
                self.connectButton.clicked.connect(self.slotDisconnect)
            self.com.timeout=0
            self.timer.start(30)
        except (serial.SerialException,ValueError) as e:
            print(e)

    def slotDisconnect(self):
        self.timer.stop()
        self.com.close()
        self.connectButton.setText("连接")
        self.connectButton.clicked.connect(self.slotConnect)

    def update(self):
        self.string=self.string+self.com.readall().decode("UTF-8")
        if self.string=='':
            return
        lines=self.string.split('\r\n')
        if self.string[-1]!='\n':
            self.string=lines[-1]
            lines.pop()
        else:
            self.string=''
        for line in lines:
            line=line.strip().split()
            for i in range(self.lineNum):
                try:
                    self.data[i][0:-1]=self.data[i][1:]
                    self.data[i][-1]=float(line[i])
                except (ValueError,IndexError):
                    continue


        self.curve.setData(self.data[0])
        if self.com.isOpen()==False:
            self.timer.stop()


            






if __name__=="__main__":
    app=pg.mkQApp()
    win=MainWindow()
    win.show()
    app.exec_()