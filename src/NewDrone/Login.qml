import QtQuick.Layouts 1.4
import QtQuick 2.1
import QtQuick.Controls 2.4
import QGroundControl 1.0
import QGroundControl.Controllers 1.0

//import QtQuick.Controls 1.4
//import QtQuick.Controls.Styles 1.4
import NewDrone.Controls 1.0
import NewDrone.Controllers 1.0

Item {

    property var margin: 5
    property var m2: 3

    LoginController {
        id: loginController
    }

    Loader {
        id: rootWindowLoader
        asynchronous: true
        anchors.fill: parent
        visible: false
        onLoaded: {
            progressOverlay.close()
            loginMainWindow.hide()
        }
    }

    Rectangle {
        color: "black"
        anchors.fill: parent

        Rectangle {
            color: "white"

            anchors.centerIn: parent
            width: parent.width / 4
            height: parent.width / 3

            ColumnLayout {

                anchors.fill: parent

                // anchors.margins: margin
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 45
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.topMargin: 0
                    //Layout.rightMargin: 10
                    //Layout.leftMargin: 10
                    color: "pink"
                    ColumnLayout {
                        anchors.fill: parent
                        Label {
                            text: "Veuillez vous connecter"
                            color: "white"
                            Layout.alignment: Qt.AlignCenter
                            font.bold: true
                        }
                    }
                }

                Image {
                    source: "/res/resources/icons/mainlogo.png"
                    fillMode: Image.Stretch

                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: parent.width * sourceSize.height / sourceSize.width
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                    Label {
                        text: "Username"
                        color: "gray"
                        Layout.alignment: Qt.AlignCenter

                        //Layout.rightMargin: 20
                    }

                    TextField {
                        id: usernameField
                        Layout.alignment: Qt.AlignCenter
                        inputMethodHints: Qt.ImhNoAutoUppercase
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

                    Label {
                        text: "Mot de Passe"
                        color: "gray"
                        Layout.alignment: Qt.AlignCenter
                        //Layout.rightMargin: 20
                    }

                    TextField {
                        id: passwordField
                        Layout.alignment: Qt.AlignCenter
                        echoMode: TextInput.Password
                    }
                }

                Button {
                    Layout.alignment: Qt.AlignCenter
                    Layout.topMargin: 20
                    text: "Connexion"

                    onClicked: {
                        var username = usernameField.text
                        if (loginController.login(username,
                                                  passwordField.text)) {
                            var role = loginController.getRole(username);
                            if (role === "Admin") {
                                console.log("ADMIN LOGIN")
                                adminSettings.open()
                            } else if (role === "SuperAdmin") {
                                console.log("SUPERADMIN LOGIN")
                                superAdminSettings.open()
                            } else if (role === "User") {
                                progressOverlay.open()
                                console.log("Logged in as user " + username)
                                loginController.loadMainWindow()
                                rootWindowLoader.setSource("")
                                rootWindowLoader.setSource(
                                            "qrc:/qml/MainRootWindow.qml")
                                rootWindowLoader.focus = true
                            }
                        } else {
                            errorLogin.open()
                        }
                        usernameField.text = ""
                        passwordField.text = ""
                    }
                }
            }
        }
    }

    Dialog {
        id: errorLogin
        modal: true
        title: "Error"
        standardButtons: Dialog.Ok
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        Label {
            text: "Mauvaise combinaison username/mot de passe"
        }
    }

    Popup {
        id: progressOverlay

        parent: Overlay.overlay

        closePolicy: Popup.NoAutoClose
        modal: true

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 100
        height: 100

        BusyIndicator {
            anchors.fill: parent
        }
    }

    AdminSettings {
        id: adminSettings
        width: parent.width
        height: parent.height
        visible: true
    }

    SuperAdminSettings {
        id: superAdminSettings
        width: parent.width
        height: parent.height
        visible: false
    }

    SimpleDialog {

        id: doneDialog
        title: "Ok"
    }
}