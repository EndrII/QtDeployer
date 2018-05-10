import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Page {
	clip: true

    header: Header {
        message: qsTr("Result")
    }


	ListView {
		id: listview
        anchors.fill: parent
		ScrollBar.vertical: ScrollBar {}

		model: VisualItemModel {
			ExtendableView {
				checkable: false
                title: qsTr("Qt Libraries")
				model: CppManager.qtLibraries
			}

			ExtendableView {
				checkable: false
                title: qsTr("Non-Qt Libraries")
				model: CppManager.cppLibraries
			}

			ExtendableView {
				checkable: false
                title: qsTr("Unknown Libraries")
				model: CppManager.notFoundLibs
			}

			ExtendableView {
				checkable: false
                title: qsTr("Qml Imports")
				model: QmlManager.foundImports
			}

			ExtendableView {
				checkable: false
                title: qsTr("Failed Qml Imports")
				model: QmlManager.notFoundImports
			}

			ExtendableView {
				checkable: true
                title: qsTr("Copied Paths")
				model: OutputManager.pathsToCopy
			}
		}
    }
}
