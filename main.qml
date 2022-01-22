import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2

Window {
    id: window
    visible: true

    width: 680
    height: 350
    property alias teLog: teLog
    title: "Hello calc"

    signal qmlSignal(string msg)
    signal qmlNumBtSignal(double val);
    signal qmlOperBtSignal(string str);
    signal qmlCalcBtSignal();
    signal qmlClearBtSignal();
    signal qmlSpinDelaySignal(int val);

    TextField {
        id: teScreen
        objectName: "teScreen"
        y: 14
        width: 312
        height: 40
        property alias text: teScreen.text
        text: ""
        anchors.left: parent.left
        anchors.leftMargin: 16
        font.weight: Font.Bold
        horizontalAlignment: Text.AlignLeft
    }

    Button {
        id: bt0
        objectName: "bt0"
        y: 204
        text: qsTr("0")
        font.weight: Font.Bold
        rotation: 0
        anchors.left: parent.left
        anchors.leftMargin: 16
        onClicked: qmlNumBtSignal(0)
    }

    Button {
        id: bt1
        objectName: "bt1"
        y: 158
        text: qsTr("1")
        font.weight: Font.Bold
        anchors.left: parent.left
        anchors.leftMargin: 16
        onClicked: qmlNumBtSignal(1)
    }

    Button {
        id: bt2
        objectName: "bt2"
        x: 122
        y: 158
        text: qsTr("2")
        font.weight: Font.Bold
        onClicked: qmlNumBtSignal(2)
    }

    Button {
        id: bt3
        objectName: "bt3"
        x: 228
        y: 158
        text: qsTr("3")
        font.weight: Font.Bold
        onClicked: qmlNumBtSignal(3)
    }

    Button {
        id: bt4
        objectName: "bt4"
        y: 112
        text: qsTr("4")
        font.weight: Font.Bold
        anchors.left: parent.left
        anchors.leftMargin: 16
        onClicked: qmlNumBtSignal(4)
    }

    Button {
        id: bt5
        objectName: "bt5"
        x: 122
        y: 112
        text: qsTr("5")
        font.weight: Font.Bold
        onClicked: qmlNumBtSignal(5)
    }

    Button {
        id: bt6
        objectName: "bt6"
        x: 228
        y: 112
        text: qsTr("6")
        font.weight: Font.Bold
        onClicked: qmlNumBtSignal(6)
    }

    Button {
        id: bt7
        objectName: "bt7"
        y: 66
        text: qsTr("7")
        font.capitalization: Font.SmallCaps
        font.weight: Font.Bold
        highlighted: false
        clip: false
        smooth: true
        antialiasing: false
        anchors.left: parent.left
        anchors.leftMargin: 16
        autoRepeat: false
        autoExclusive: false
        checked: false
        checkable: false
        onClicked: qmlNumBtSignal(7)
    }

    Button {
        id: bt8
        objectName: "bt8"
        x: 5
        y: 66
        text: qsTr("8")
        checkable: false
        font.weight: Font.Bold
        antialiasing: false
        anchors.leftMargin: 122
        anchors.left: parent.left
        checked: false
        smooth: true
        autoExclusive: false
        highlighted: false
        autoRepeat: false
        clip: false
        font.capitalization: Font.SmallCaps
        onClicked: qmlNumBtSignal(8)
    }

    Button {
        id: bt9
        objectName: "bt9"
        x: 5
        y: 66
        text: qsTr("9")
        font.weight: Font.Bold
        checkable: false
        antialiasing: false
        anchors.leftMargin: 228
        anchors.left: parent.left
        smooth: true
        checked: false
        highlighted: false
        autoExclusive: false
        autoRepeat: false
        clip: false
        font.capitalization: Font.SmallCaps
        onClicked: qmlNumBtSignal(9)
    }

    Button {
        id: btCalc
        objectName: "btCalc"
        x: 122
        y: 204
        width: 206
        height: 40
        text: qsTr("=")
        font.weight: Font.Bold
        onClicked: qmlCalcBtSignal()
    }

    Button {
        id: btDiv
        objectName: "btDiv"
        x: 334
        y: 66
        text: qsTr("/")
        font.weight: Font.Bold
        onClicked: qmlOperBtSignal("/")
    }

    Button {
        id: btMult
        objectName: "btMult"
        x: 334
        y: 112
        text: qsTr("x")
        font.weight: Font.Bold
        onClicked: qmlOperBtSignal("x")
    }

    Button {
        id: btSub
        objectName: "btSub"
        x: 334
        y: 158
        text: qsTr("-")
        font.weight: Font.Bold
        onClicked: qmlOperBtSignal("-")
    }

    Button {
        id: btAdd
        objectName: "btAdd"
        x: 334
        y: 204
        text: qsTr("+")
        font.weight: Font.Bold
        onClicked: qmlOperBtSignal("+")
    }

    Button {
        id: btClear
        objectName: "btClear"
        x: 334
        y: 14
        text: qsTr("clear")
        font.weight: Font.Bold
        onClicked: qmlClearBtSignal()
    }

    GroupBox {
        id: groupBox
        objectName: "groupBox"
        x: 440
        y: 17
        width: 226
        height: 232
        title: qsTr("control")

        SpinBox {
            id: spinBox
            objectName: "spinBox"
            y: 109
            width: 120
            height: 40
            value: 1
            onValueModified: qmlSpinDelaySignal(value)
        }

        TextField {
            id: tfReq
            y: 15
            width: 80
            height: 40
            objectName: "tfReq"
            text: qsTr("0")
            transformOrigin: Item.Center
            clip: false
        }

        TextField {
            id: tfRes
            objectName: "tfRes"
            y: 61
            width: 80
            height: 40
            text: qsTr("0")
            transformOrigin: Item.Center
            clip: false
        }

        Label {
            id: label
            y: 24
            width: 120
            text: qsTr("Request size")
            clip: true
            anchors.verticalCenterOffset: 0
            anchors.left: tfReq.right
            anchors.leftMargin: 6
            anchors.verticalCenter: tfReq.verticalCenter
        }

        Label {
            id: label1
            y: 70
            width: 120
            text: qsTr("Result size")
            clip: true
            anchors.left: tfRes.right
            anchors.leftMargin: 6
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: tfRes.verticalCenter
        }

        Label {
            id: label2
            y: 118
            width: 120
            text: qsTr("delay sec")
            anchors.verticalCenter: spinBox.verticalCenter
            anchors.left: spinBox.right
            anchors.leftMargin: 6
        }
    }

    TextField {
        id: teLog
        objectName: "teLog"
        y: 255
        width: 650
        height: 42

        text: qsTr("log...")
        placeholderText: qsTr("")
        transformOrigin: Item.Center
        wrapMode: Text.WordWrap
        clip: true
        horizontalAlignment: Text.AlignLeft
        anchors.left: parent.left
        anchors.leftMargin: 16
        font.weight: Font.Normal
    }

}
