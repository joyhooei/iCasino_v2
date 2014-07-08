LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/boost4a
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/boost
LOCAL_LDLIBS += -L$(LOCAL_PATH)/../../../../libs/boost4a/lib
LOCAL_LDLIBS += -lboost_system-gcc-mt-1_52 -lboost_thread-gcc-mt-1_52 -lboost_regex-gcc-mt-1_52

LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -frtti

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/cocos2dx/platform
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Controllers
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Bitswarm
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Bitswarm/BBox
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Http
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Core/Sockets
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Core
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Entities/Data
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Entities/Invitation
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Entities/Managers
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Entities/Match
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Entities/Variables
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Entities
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Exceptions
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/FSM
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Logging
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Protocol/Serialization
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Requests/Buddylist
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Requests/Game
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Requests
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Util/md5
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Util
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../libs/smartfox/Util/XMLParser
LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AllData.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/BaCayChuong.cpp \
../../Classes/BaCayNormal.cpp \
../../Classes/Card.cpp \
../../Classes/CardChan.cpp \
../../Classes/CustomTableViewCell.cpp \
../../Classes/FrameBet.cpp \
../../Classes/GameServer.cpp \
../../Classes/LayerAction.cpp \
../../Classes/LayerAvatarXiTo.cpp \
../../Classes/LayerBet_BaCayChuong.cpp \
../../Classes/LayerBet_TomCuaCa.cpp \
../../Classes/LayerBet_Lieng.cpp \
../../Classes/LayerBorrowMoney.cpp \
../../Classes/LayerBuyAvatar.cpp \
../../Classes/LayerAvatar_BaCay.cpp \
../../Classes/_CardBaCay_.cpp \
../../Classes/_LayerBet_.cpp \
../../Classes/LayerChanGame.cpp \
../../Classes/LayerChangeAvatar.cpp \
../../Classes/LayerChangePassword.cpp \
../../Classes/LayerChargeMoney.cpp \
../../Classes/LayerChatRoom.cpp \
../../Classes/LayerChonBanChoi.cpp \
../../Classes/LayerChooseGame.cpp \
../../Classes/LayerCreateAccount.cpp \
../../Classes/LayerCreateRoom.cpp \
../../Classes/LayerCurrencyExchange.cpp \
../../Classes/LayerForgotPassword.cpp \
../../Classes/LayerFriend.cpp \
../../Classes/LayerFriendDetails.cpp \
../../Classes/LayerGameChan_KetQua.cpp \
../../Classes/LayerGameChan_XuongU.cpp \
../../Classes/LayerInbox.cpp \
../../Classes/LayerInviteFriends.cpp \
../../Classes/LayerLichSuGiaoDich.cpp \
../../Classes/LayerLoading.cpp \
../../Classes/LayerLogin.cpp \
../../Classes/LayerMain.cpp \
../../Classes/LayerMoiChoi.cpp \
../../Classes/LayerMoney.cpp \
../../Classes/LayerNotification.cpp \
../../Classes/LayerOpenCard_Xito.cpp \
../../Classes/LayerPasswordRoom.cpp \
../../Classes/LayerPlayerInfo.cpp \
../../Classes/LayerPlayGame.cpp \
../../Classes/LayerPlayGameChinessChess.cpp \
../../Classes/LayerPlayGamePhom.cpp \
../../Classes/LayerPlayGameTLMB.cpp \
../../Classes/LayerPlayGameTLMN.cpp \
../../Classes/LayerServices.cpp \
../../Classes/LayerSettings.cpp \
../../Classes/LayerSMS.cpp \
../../Classes/LayerTransferMoney.cpp \
../../Classes/LayerTyGia.cpp \
../../Classes/LayerUpdateInfo.cpp \
../../Classes/LayerUserInfo.cpp \
../../Classes/LayerUserInfo_Details.cpp \
../../Classes/Lieng.cpp \
../../Classes/LogicInChess.cpp \
../../Classes/Nan3Cay.cpp \
../../Classes/SceneManager.cpp \
../../Classes/TomCuaCa.cpp \
../../Classes/XiTo.cpp \
../../Classes/_Avatar_.cpp \
../../Classes/_Avatar_inGame_.cpp \
../../Classes/_Avatar_inTomCuaCa.cpp \
../../Classes/_Background_inGame_.cpp \
../../Classes/_Button_.cpp \
../../Classes/_Button_inGame_.cpp \
../../Classes/_Button_inMain_.cpp \
../../Classes/_Card_.cpp \
../../Classes/_Card_inGame_.cpp \
../../Classes/_Chat_.cpp \
../../Classes/_Chat_inGame_.cpp \
../../Classes/_Chess_.cpp \
../../Classes/_Layer_CardChan_.cpp \
../../Classes/_Number_.cpp \
../../Classes/_Number_inGame_.cpp \
../../Classes/_Number_inTomCuaCa.cpp \
../../Classes/LayerChatWindow.cpp \
../../Classes/Android.cpp \
    ../../../../libs/smartfox/SmartFox.cpp \
    ../../../../libs/smartfox/Bitswarm/BBox/BBClient.cpp \
    ../../../../libs/smartfox/Bitswarm/BBox/BBEvent.cpp \
    ../../../../libs/smartfox/Bitswarm/BaseController.cpp \
    ../../../../libs/smartfox/Bitswarm/BitSwarmClient.cpp \
    ../../../../libs/smartfox/Bitswarm/BitSwarmEvent.cpp \
    ../../../../libs/smartfox/Bitswarm/ConnectionModes.cpp   \
    ../../../../libs/smartfox/Bitswarm/Message.cpp \
    ../../../../libs/smartfox/Bitswarm/PendingPacket.cpp \
    ../../../../libs/smartfox/Bitswarm/UDPManager.cpp \
    ../../../../libs/smartfox/Controllers/ExtensionController.cpp \
    ../../../../libs/smartfox/Controllers/SystemController.cpp \
    ../../../../libs/smartfox/Core/Sockets/IPAddress.cpp \
    ../../../../libs/smartfox/Core/Sockets/TCPClient.cpp \
    ../../../../libs/smartfox/Core/Sockets/TCPSocketLayer.cpp \
    ../../../../libs/smartfox/Core/Sockets/UDPClient.cpp \
    ../../../../libs/smartfox/Core/Sockets/UDPSocketLayer.cpp \
    ../../../../libs/smartfox/Core/BaseEvent.cpp \
    ../../../../libs/smartfox/Core/PacketHeader.cpp \
    ../../../../libs/smartfox/Core/SFSBuddyEvent.cpp \
    ../../../../libs/smartfox/Core/SFSEvent.cpp \
    ../../../../libs/smartfox/Core/SFSIOHandler.cpp \
    ../../../../libs/smartfox/Core/SFSProtocolCodec.cpp \
    ../../../../libs/smartfox/Core/ThreadManager.cpp \
    ../../../../libs/smartfox/Entities/Data/SFSArray.cpp \
    ../../../../libs/smartfox/Entities/Data/SFSDataWrapper.cpp \
    ../../../../libs/smartfox/Entities/Data/SFSObject.cpp \
    ../../../../libs/smartfox/Entities/Invitation/SFSInvitation.cpp \
    ../../../../libs/smartfox/Entities/Managers/SFSBuddyManager.cpp \
    ../../../../libs/smartfox/Entities/Managers/SFSGlobalUserManager.cpp \
    ../../../../libs/smartfox/Entities/Managers/SFSRoomManager.cpp \
    ../../../../libs/smartfox/Entities/Managers/SFSUserManager.cpp \
    ../../../../libs/smartfox/Entities/Match/BoolMatch.cpp \
    ../../../../libs/smartfox/Entities/Match/LogicOperator.cpp \
    ../../../../libs/smartfox/Entities/Match/MatchExpression.cpp \
    ../../../../libs/smartfox/Entities/Match/NumberMatch.cpp \
    ../../../../libs/smartfox/Entities/Match/RoomProperties.cpp \
    ../../../../libs/smartfox/Entities/Match/StringMatch.cpp \
    ../../../../libs/smartfox/Entities/Match/UserProperties.cpp \
    ../../../../libs/smartfox/Entities/Variables/ReservedBuddyVariables.cpp \
    ../../../../libs/smartfox/Entities/Variables/ReservedRoomVariables.cpp \
    ../../../../libs/smartfox/Entities/Variables/SFSBuddyVariable.cpp \
    ../../../../libs/smartfox/Entities/Variables/SFSRoomVariable.cpp \
    ../../../../libs/smartfox/Entities/Variables/SFSUserVariable.cpp \
    ../../../../libs/smartfox/Entities/SFSBuddy.cpp \
    ../../../../libs/smartfox/Entities/SFSConstants.cpp \
    ../../../../libs/smartfox/Entities/SFSRoom.cpp \
    ../../../../libs/smartfox/Entities/SFSUser.cpp \
    ../../../../libs/smartfox/Exceptions/SFSCodecError.cpp \
    ../../../../libs/smartfox/Exceptions/SFSError.cpp \
    ../../../../libs/smartfox/Exceptions/SFSValidationError.cpp \
    ../../../../libs/smartfox/FSM/FiniteStateMachine.cpp \
    ../../../../libs/smartfox/FSM/FSMState.cpp \
    ../../../../libs/smartfox/Http/SFSWebClient.cpp \
    ../../../../libs/smartfox/Logging/Logger.cpp \
    ../../../../libs/smartfox/Logging/LoggerEvent.cpp \
    ../../../../libs/smartfox/Protocol/Serialization/DefaultObjectDumpFormatter.cpp \
    ../../../../libs/smartfox/Protocol/Serialization/DefaultSFSDataSerializer.cpp \
    ../../../../libs/smartfox/Requests/Buddylist/AddBuddyRequest.cpp \
    ../../../../libs/smartfox/Requests/Buddylist/BlockBuddyRequest.cpp \
    ../../../../libs/smartfox/Requests/Buddylist/BuddyMessageRequest.cpp \
    ../../../../libs/smartfox/Requests/Buddylist/GoOnlineRequest.cpp \
    ../../../../libs/smartfox/Requests/Buddylist/InitBuddyListRequest.cpp \
    ../../../../libs/smartfox/Requests/Buddylist/RemoveBuddyRequest.cpp \
    ../../../../libs/smartfox/Requests/Buddylist/SetBuddyVariablesRequest.cpp \
    ../../../../libs/smartfox/Requests/Game/CreateSFSGameRequest.cpp \
    ../../../../libs/smartfox/Requests/Game/InvitationReplyRequest.cpp \
    ../../../../libs/smartfox/Requests/Game/InviteUsersRequest.cpp \
    ../../../../libs/smartfox/Requests/Game/QuickGameJoinRequest.cpp \
    ../../../../libs/smartfox/Requests/Game/SFSGameSettings.cpp \
    ../../../../libs/smartfox/Requests/AdminMessageRequest.cpp \
    ../../../../libs/smartfox/Requests/BanUserRequest.cpp \
    ../../../../libs/smartfox/Requests/BaseRequest.cpp \
    ../../../../libs/smartfox/Requests/ChangeRoomCapacityRequest.cpp \
    ../../../../libs/smartfox/Requests/ChangeRoomNameRequest.cpp \
    ../../../../libs/smartfox/Requests/ChangeRoomPasswordStateRequest.cpp \
    ../../../../libs/smartfox/Requests/CreateRoomRequest.cpp \
    ../../../../libs/smartfox/Requests/ExtensionRequest.cpp \
    ../../../../libs/smartfox/Requests/FindRoomsRequest.cpp \
    ../../../../libs/smartfox/Requests/FindUsersRequest.cpp \
    ../../../../libs/smartfox/Requests/GenericMessageRequest.cpp \
    ../../../../libs/smartfox/Requests/HandshakeRequest.cpp \
    ../../../../libs/smartfox/Requests/JoinRoomRequest.cpp \
    ../../../../libs/smartfox/Requests/KickUserRequest.cpp \
    ../../../../libs/smartfox/Requests/LeaveRoomRequest.cpp \
    ../../../../libs/smartfox/Requests/LoginRequest.cpp \
    ../../../../libs/smartfox/Requests/LogoutRequest.cpp \
    ../../../../libs/smartfox/Requests/ManualDisconnectionRequest.cpp \
    ../../../../libs/smartfox/Requests/MessageRecipientMode.cpp \
    ../../../../libs/smartfox/Requests/ModeratorMessageRequest.cpp \
    ../../../../libs/smartfox/Requests/ObjectMessageRequest.cpp \
    ../../../../libs/smartfox/Requests/PingPongRequest.cpp \
    ../../../../libs/smartfox/Requests/PlayerToSpectatorRequest.cpp \
    ../../../../libs/smartfox/Requests/PrivateMessageRequest.cpp \
    ../../../../libs/smartfox/Requests/PublicMessageRequest.cpp \
    ../../../../libs/smartfox/Requests/RoomEvents.cpp \
    ../../../../libs/smartfox/Requests/RoomExtension.cpp \
    ../../../../libs/smartfox/Requests/RoomPermissions.cpp \
    ../../../../libs/smartfox/Requests/RoomSettings.cpp \
    ../../../../libs/smartfox/Requests/SetRoomVariablesRequest.cpp \
    ../../../../libs/smartfox/Requests/SetUserVariablesRequest.cpp \
    ../../../../libs/smartfox/Requests/SpectatorToPlayerRequest.cpp \
    ../../../../libs/smartfox/Requests/SubscribeRoomGroupRequest.cpp \
    ../../../../libs/smartfox/Requests/UnsubscribeRoomGroupRequest.cpp \
    ../../../../libs/smartfox/Util/md5/md5.c \
    ../../../../libs/smartfox/Util/ByteArray.cpp \
    ../../../../libs/smartfox/Util/ClientDisconnectionReason.cpp \
    ../../../../libs/smartfox/Util/ConfigData.cpp \
    ../../../../libs/smartfox/Util/ConfigLoader.cpp \
    ../../../../libs/smartfox/Util/EventDispatcher.cpp \
    ../../../../libs/smartfox/Util/LagMonitor.cpp \
    ../../../../libs/smartfox/Util/SFSErrorCodes.cpp \
    ../../../../libs/smartfox/Util/XMLParser/XMLNode.cpp \
    ../../../../libs/smartfox/Util/XMLParser/XMLNodeList.cpp \
    ../../../../libs/smartfox/Util/XMLParser/XMLNodeValue.cpp \
    ../../../../libs/smartfox/Util/XMLParser/XMLObject.cpp \
    ../../../../libs/smartfox/Util/XMLParser/XMLParser.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/cocos2dx/platform/android/jni

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)

