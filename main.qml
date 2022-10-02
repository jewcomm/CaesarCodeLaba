import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12

Window {
    width: 900
    height: 800
    visible: true
    title: qsTr("Hello World")

    property int fontSize: 22
    property int modeCoder: 1

    Connections {
        target: coder
        onGetAlphabet:{
            usingAlphabet.text = alphabet
        }

        onGetMutAlphabet:{
            usingMutAlphabet.text = mutAlphabet
        }

        onGetCoderedText:{
            coderedText.text = text
        }

        onGetDecoderedText:{
            originalText.text = text
        }
    }

    GridLayout {
        anchors.fill: parent
        Layout.margins: 10
        ButtonGroup { id: buttonModeAlphabetGroup }

        ColumnLayout {
            RadioButton {
                id: fullButton
                checked: true
                ButtonGroup.group: buttonModeAlphabetGroup
                text: qsTr("Полный алфавит")
                font.pointSize: fontSize
                onPressed: {
                    coder.changemodeAlphabet(1)
                    modeCoder = 1
                }
            }

            RadioButton {
                id: withoutEButton
                ButtonGroup.group: buttonModeAlphabetGroup
                text: qsTr("Алфавит без буквы 'ё'")
                font.pointSize: fontSize
                onPressed: {
                    coder.changemodeAlphabet(4)
                    modeCoder = 4
                }
            }

            RadioButton {
                id: withoutIButton
                ButtonGroup.group: buttonModeAlphabetGroup
                text: qsTr("Алфавит без буквы 'й'")
                font.pointSize: fontSize
                onPressed: {
                    coder.changemodeAlphabet(3)
                    modeCoder = 3
                }
            }

            RadioButton {
                id: withoutEIButton
                ButtonGroup.group: buttonModeAlphabetGroup
                text: qsTr("Алфавит без буквы 'ё' и 'й'")
                font.pointSize: fontSize
                onPressed: {
                    coder.changemodeAlphabet(2)
                    modeCoder = 2
                }
            }
            Layout.row: 0
            Layout.column: 0
            Layout.columnSpan: 4
        }

        Text {
            text: qsTr("Сдвиг: ")
            font.pointSize: fontSize
            Layout.row: 1
            Layout.column: 0
        }

        TextField {
            id: shiftValue
            text: "1"
            inputMask: "Dd"
            font.pointSize: fontSize
            Layout.row: 1
            Layout.column: 1
            onEditingFinished: {
                if(focus === true) {
                    focus = false
                    return;
                }
                coder.setShift(this.text)
            }
        }

        ButtonGroup { id: codeDecodeGroup }

        RadioButton {
            id: codedMode
            ButtonGroup.group: codeDecodeGroup
            checked: true
            text: qsTr("Кодирование")
            font.pointSize: fontSize
            Layout.row: 1
            Layout.column: 2
            onPressed: {
                coder.changeModeCode(false);
            }
        }

        RadioButton {
            id: decodedMode
            ButtonGroup.group: codeDecodeGroup
            text: qsTr("Декодирование")
            font.pointSize: fontSize
            Layout.row: 1
            Layout.column: 3
            onPressed: {
                coder.changeModeCode(true);
            }
        }

        Text {
            text: qsTr("Используемый алфавит: ")
            font.pointSize: fontSize
            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 4
        }

        TextField {
            id: usingAlphabet
            text: "абвгдеёжзийклмнопрстуфхцчшщъыьэюя" // костыль, но я хз как его поправить
            font.pointSize: fontSize
            Layout.fillWidth: true
            Layout.row: 3
            Layout.column: 0
            Layout.columnSpan: 4
            onFocusChanged: {
                if(focus === true) focus = false
            }
        }

        Text {
            text: qsTr("Алфавит после сдвига: ")
            font.pointSize: fontSize
            Layout.row: 4
            Layout.column: 0
            Layout.columnSpan: 4
        }

        TextField {
            id: usingMutAlphabet
            font.pointSize: fontSize
            Layout.fillWidth: true
            Layout.row: 5
            Layout.column: 0
            Layout.columnSpan: 4
            onFocusChanged: {
                if(focus === true) focus = false
            }
        }

        Text {
            text: qsTr("Текст для кодирования:")
            font.pointSize: fontSize
            Layout.row: 6
            Layout.column: 0
            Layout.columnSpan: 4
        }

        TextField {
            id: originalText
            font.pointSize: fontSize
            validator: RegExpValidator { regExp: /[а-яё ]+/}
            onEditingFinished: {
                coder.setCoding(this.text)
            }
            onFocusChanged: {
                if(codedMode.checked === false) focus = false
            }
            Layout.row: 7
            Layout.column: 0
            Layout.columnSpan: 4
            Layout.fillWidth: true
        }

        Text {
            text: qsTr("Кодированный текст:")
            font.pointSize: fontSize
            Layout.row: 8
            Layout.column: 0
            Layout.columnSpan: 4
        }

        TextField {
            id: coderedText
            font.pointSize: fontSize
            validator: RegExpValidator { regExp: /[а-яё ]+/}
            onEditingFinished: {
                coder.setDecoding(this.text)
            }
            onFocusChanged: {
                if(decodedMode.checked === false) focus = false
            }
            Layout.row: 9
            Layout.column: 0
            Layout.columnSpan: 4
            Layout.fillWidth: true
        }

        Item {
            width: 1
            Layout.fillHeight: true
            Layout.row: 10
        }
    }
}
