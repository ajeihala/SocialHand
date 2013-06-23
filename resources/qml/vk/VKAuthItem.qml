import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtWebKit 3.0

import SocialHand 1.0

Window {
    id: windowId
    width: 800
    height: 600

    signal loginSuccess(string userId, string accessToken, string expiresIn)

    onVisibleChanged: {
        if (visible) {
            webViewId.url = "https://oauth.vk.com/authorize?client_id=3726559&scope=friends&redirect_uri=https://oauth.vk.com/blank.html&display=page&v=4.99&response_type=token"
        }
    }

    WebView {
        id: webViewId
        anchors.fill: parent
        onUrlChanged: {
            console.log("url: " + url)
            var str = url.toString()
            var regExp = /.*access_token=(.*)&expires_in=(.*)&user_id=(\d+)/

            if (regExp.test(str)) {
                console.log("access_token!")
                // https://oauth.vk.com/blank.html#access_token=1f78a7a2c3383e9fe8610ac69f7d2cf77f297e557614448551a7e8fb2486e222953d2354de9ca4d5f7b11&expires_in=86400&user_id=5848693

                var result = regExp.exec(str)

                console.log("result 1: " + result[1])
                console.log("result 2: " + result[2])
                console.log("result 3: " + result[3])

                var token = result[1]
                var userId = result[3]
                var expiresIn = result[2]

                windowId.loginSuccess(userId, token, expiresIn)

                visible = false
                url = ""
                windowId.close()

                vkAuth.saveLoginInformation(userId, token, expiresIn)
            }
        }
    }
}
