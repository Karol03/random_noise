import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Material


Window {
    Material.theme: Material.Dark
    Material.accent: Material.Purple

    readonly property color darkThemeColor: "#2C3639"
    readonly property color lightThemeColor: "#3F4E4F"
    readonly property color darkColor: "#A27B5C"
    readonly property color lightColor: "#DCD7C9"

    id: root
    width: 480
    minimumWidth: 480
    maximumWidth: 480
    height: 162
    minimumHeight: 162
    maximumHeight: 162
    visible: true
    color: darkThemeColor

    title: qsTr("Random Noise")

    Rectangle {
        width: parent.width
        height: parent.height
        color: "transparent"

        Column {
            padding: 6
            spacing: 8
            anchors.left: parent.left


            Rectangle {
                id: randomNoise
                radius: 10
                color: "transparent"
                width: maximumWidth - 2 * parent.padding
                height: (maximumHeight - parent.spacing) * 0.8 - parent.padding

                Column {
                    width: parent.width
                    padding: 12
                    spacing: 4

                    RoundButton {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("Get random noise")
                        font.pointSize: 18
                        padding: 10

                        contentItem: Text {
                            text: parent.text
                            font: parent.font
                            opacity: enabled ? 1.0 : 0.3
                            color: lightColor
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            radius: 8
                            color: parent.hovered ? "#747B97" : lightThemeColor
                        }

                        MouseArea
                        {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: engine.randomNoise = ""
                        }
                    }

                    Rectangle {
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "transparent"
                        width: parent.width
                        height: 52

                        TextEdit {
                            clip: true
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            width: parent.width - 12
                            height: parent.height
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.bold: true
                            font.pixelSize: 20
                            text: engine.randomNoise
                            color: lightColor
                            selectByMouse: true
                            readOnly: true
                        }
                    }
                }
            }

            Rectangle {
                id: status
                radius: 2
                color: lightThemeColor
                width: maximumWidth - 2 * parent.padding
                height: (maximumHeight - parent.spacing) * 0.2 - parent.padding

                TextEdit {
                    leftPadding: 6
                    clip: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    width: parent.width - 12
                    height: parent.height
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 10
                    text: engine.status
                    color: lightColor
                    selectByMouse: true
                    readOnly: true
                }
            }
        }
    }

    Connections {
      target: engine
    }
}
