import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Window

import com.models 1.0
import com.others 1.0

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("File System Watcher")

    EventsModel {
        id: eventsModel
    }

    WatchedPathsModel {
        id: watchedPathsModel
    }

    FileSystemWatcher {
        id: fileSystemWatcher
    }

    ColumnLayout {
        spacing: 5
        anchors.fill: parent
        anchors.margins: 10

        FolderDialog {
            id: folderDialog
            onAccepted: {
                watchedPathsModel.addPath(folderDialog.selectedFolder)
            }
        }

        RowLayout {
            Label {
                text: qsTr("Watched paths")
            }
            Item {
                Layout.fillWidth: true
            }
            Button {
                text: qsTr("Add")
                onClicked: {
                    folderDialog.open()
                }
                enabled: !fileSystemWatcher.isRunning
            }
        }

        ListView {
            id: watchedPathsListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: watchedPathsModel
            delegate: RowLayout {
                spacing: 5
                width: watchedPathsListView.width
                Text {
                    Layout.fillWidth: true
                    Layout.leftMargin: 5
                    text: model.path
                    elide: Text.ElideMiddle
                }
                Button {
                    text: qsTr("Remove")
                    Layout.rightMargin: 10
                    Layout.topMargin: 5
                    onClicked: {
                        watchedPathsModel.removeRow(index)
                    }
                    enabled: !fileSystemWatcher.isRunning
                }
            }
            Rectangle {
                z: parent.z - 1
                anchors.fill: parent
                border {
                    color: "black"
                    width: 1
                }
                radius: 10
                visible: true
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            border {
                color: "black"
                width: 1
            }
            radius: 10

            HorizontalHeaderView {
                id: eventsTableViewHeader
                syncView: eventsTableView
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    margins: 10
                }
            }

            TableView {
                id: eventsTableView
                anchors {
                    top: eventsTableViewHeader.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                    margins: 10
                }
                clip: true
                boundsBehavior: Flickable.DragOverBounds
                model: eventsModel
                columnWidthProvider: function (column) {
                    switch (column)
                    {
                    case 0:
                        return eventsTableView.width * 0.2
                    case 1:
                        return eventsTableView.width * 0.5
                    case 2:
                        return eventsTableView.width * 0.1
                    case 3:
                        return eventsTableView.width * 0.2
                    default:
                        return 0
                    }
                }
                onWidthChanged: {
                   eventsTableView.forceLayout()
                }
                delegate: Rectangle {
                    id: delegate
                    implicitHeight: 20
                    implicitWidth: eventsTableView.columnWidthProvider()
                    Text {
                        anchors.fill: parent
                        text: model.cellValue
                        elide: Text.ElideMiddle
                    }
                }
            }
        }

        RowLayout {
            Button {
                text: qsTr("Clear")
                onClicked: {
                    fileSystemWatcher.clear()
                }
            }
            Button {
                text: qsTr("Start")
                onClicked: {
                    fileSystemWatcher.start()
                }
                enabled: !fileSystemWatcher.isRunning
            }
            Button {
                text: qsTr("Stop")
                onClicked: {
                    fileSystemWatcher.stop()
                }
                enabled: fileSystemWatcher.isRunning
            }
            Item {
                Layout.fillWidth: true
            }
        }
    }
}
