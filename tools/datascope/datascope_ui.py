# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '.\datascope.ui'
#
# Created by: PyQt5 UI code generator 5.10
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(597, 623)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.plotView = PlotWidget(self.centralwidget)
        self.plotView.setGeometry(QtCore.QRect(11, 11, 571, 521))
        self.plotView.setObjectName("plotView")
        self.widget = QtWidgets.QWidget(self.centralwidget)
        self.widget.setGeometry(QtCore.QRect(19, 556, 548, 30))
        self.widget.setObjectName("widget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.widget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.comLabel = QtWidgets.QLabel(self.widget)
        self.comLabel.setObjectName("comLabel")
        self.horizontalLayout.addWidget(self.comLabel)
        self.comEdit = QtWidgets.QLineEdit(self.widget)
        self.comEdit.setText("")
        self.comEdit.setFrame(True)
        self.comEdit.setObjectName("comEdit")
        self.horizontalLayout.addWidget(self.comEdit)
        self.baudrateLabel = QtWidgets.QLabel(self.widget)
        self.baudrateLabel.setObjectName("baudrateLabel")
        self.horizontalLayout.addWidget(self.baudrateLabel)
        self.baudrateEdit = QtWidgets.QLineEdit(self.widget)
        self.baudrateEdit.setInputMask("")
        self.baudrateEdit.setText("")
        self.baudrateEdit.setObjectName("baudrateEdit")
        self.horizontalLayout.addWidget(self.baudrateEdit)
        self.connectButton = QtWidgets.QPushButton(self.widget)
        self.connectButton.setObjectName("connectButton")
        self.horizontalLayout.addWidget(self.connectButton)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusBar = QtWidgets.QStatusBar(MainWindow)
        self.statusBar.setObjectName("statusBar")
        MainWindow.setStatusBar(self.statusBar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.comLabel.setText(_translate("MainWindow", " 端口"))
        self.baudrateLabel.setText(_translate("MainWindow", "波特率"))
        self.connectButton.setText(_translate("MainWindow", "连接"))

from pyqtgraph import PlotWidget
