import QtQml 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import Synth 1.0

Rectangle {
    width: 720
    height: 480

    PreviewController {
        id: previewController
    }

    Row {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 12
        spacing: 6

        SpinBox {
            id: frequency
            from: 0
            to: 18000
            Binding {
                target: previewController
                property: "frequency"
                value: frequency.value
            }
            value: previewController.frequency
        }

        Button {
            id: playButton
            property var playState: PreviewController.Stopped
            text: qsTr("Play")

            Connections {
                target: previewController
                function onStatusChanged() {
                    playButton.playState = previewController.status
                    if (playButton.playState == PreviewController.Stopped) 
                    {
                        playButton.text = qsTr("Play");
                    }
                    else if (playButton.playState == PreviewController.Playing)
                    {
                        playButton.text = qsTr("Stop");
                    }
                }
            }

            onClicked: {
                if (playState == PreviewController.Stopped) 
                {
                    previewController.play();
                }
                else
                {
                    previewController.stop();
                }
            }
        }
        
        Component.onCompleted: {
            previewController.setSource();
        }
    }
}
