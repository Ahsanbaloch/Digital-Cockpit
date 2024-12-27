import QtQuick 2.15
import QtQuick.Controls 2.15
import com.example.vcan 1.0

Window 
{
    width: 1024
    height: 600
    visible: true
    title: qsTr("Digital Cockpit")
    
    Rectangle
    {
        anchors.fill: parent
        color: "#1e1e1e" 
    //Speedometer
        Rectangle
        {
            id: speedometer
            width: 300
            height: 300
            radius: width / 2
            color: "#2a2a2a"
            border.color: "#3a3a3a"
            border.width: 2
            anchors.centerIn: parent

            Text
            {
                anchors.centerIn: parent
                text: vcan.framePayload
                font.pixelSize: 72
                color: "white"
            }

            Text
            {
                anchors.top: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "km/h"
                font.pixelSize: 24
                color: "white"
            }
        }

        // RPM Gauge placeholder
        Rectangle
        {
            width: 200
            height: 200
            radius: width / 2
            color: "#2a2a2a"
            border.color: "#3a3a3a"
            border.width: 2
            anchors.right: speedometer.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 50

            Text
            {
                anchors.centerIn: parent
                text: "RPM"
                font.pixelSize: 24
                color: "white"
            }
        }

        // Fuel Gauge (placeholder)
        Rectangle 
        {
            width: 200
            height: 200
            radius: width / 2
            color: "#2a2a2a"
            border.color: "#3a3a3a"
            border.width: 2
            anchors.left: speedometer.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 50

            Text 
            {
                anchors.centerIn: parent
                text: "Fuel"
                font.pixelSize: 24
                color: "white"
            }
        }

        //warning lights (placeholders)
        Row
        {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            spacing: 20

            Repeater
            {
                model: ["Engine", "Oil", "Battery", "Brake"]
                delegate: Rectangle
                {
                    width: 50
                    height: 50
                    radius: 25
                    color: "#3a3a3a"

                    Text
                    {
                        anchors.centerIn: parent
                        text: modelData[0]
                        font.pixelSize: 18
                        color: "white"
                    }
                }
            }
        }

        //Additional Info
        Column
        {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 20
            spacing: 10

            Text
            {
                text: "Outside Temp: 22C"
                font.pixelSize: 18
                color: "White"
            }

            Text
            {
                text: "Time: " + new Date().toLocaleTimeString(Qt.locale(), "hh:mm")
                font.pixelSize: 18
                color: "white"
            }
        }
    }



    // Column {
    //     anchors.centerIn: parent
    //     spacing: 10
    //     Text {
    //         text: "Frame Payload:"
    //         font.pixelSize: 18
    //     }
    //     Rectangle {
    //         width: 300
    //         height: 50
    //         border.color: "black"
    //         border.width: 1
    //         Text {
    //             anchors.centerIn: parent
    //             text: vcan.framePayload
    //             font.pixelSize: 16
    //         }
    //     }
    // }
}
