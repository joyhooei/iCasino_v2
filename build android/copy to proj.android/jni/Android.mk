LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/boost4a
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/boost
LOCAL_LDLIBS += -L$(LOCAL_PATH)/../../../../lib/boost4a/lib
LOCAL_LDLIBS+= -lboost_system-gcc-mt-1_52 -lboost_thread-gcc-mt-1_52 -lboost_regex-gcc-mt-1_52

LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -frtti

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/cocos2dx/platform
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Controllers
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Bitswarm
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Bitswarm/BBox
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Http
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Core/Sockets
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Core
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Entities/Data
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Entities/Invitation
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Entities/Managers
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Entities/Match
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Entities/Variables
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Entities
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Exceptions
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/FSM
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Logging
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Protocol/Serialization
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Requests/Buddylist
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Requests/Game
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Requests
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Util/md5
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Util
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../lib/smartfox/Util/XMLParser
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
../../Classes/ImageDownloader.cpp \
../../Classes/LayerGameChan_XuongU2.cpp \
../../Classes/_Number_Chat_inGame7u.cpp \
../../Classes/Layer_GivePocker_Chan.cpp \
	../../../../cocos2dx/platform/android/jni/Android.cpp \
    ../../../../lib/smartfox/SmartFox.cpp \
    ../../../../lib/smartfox/Bitswarm/BBox/BBClient.cpp \
    ../../../../lib/smartfox/Bitswarm/BBox/BBEvent.cpp \
    ../../../../lib/smartfox/Bitswarm/BaseController.cpp \
    ../../../../lib/smartfox/Bitswarm/BitSwarmClient.cpp \
    ../../../../lib/smartfox/Bitswarm/BitSwarmEvent.cpp \
    ../../../../lib/smartfox/Bitswarm/ConnectionModes.cpp   \
    ../../../../lib/smartfox/Bitswarm/Message.cpp \
    ../../../../lib/smartfox/Bitswarm/PendingPacket.cpp \
    ../../../../lib/smartfox/Bitswarm/UDPManager.cpp \
    ../../../../lib/smartfox/Controllers/ExtensionController.cpp \
    ../../../../lib/smartfox/Controllers/SystemController.cpp \
    ../../../../lib/smartfox/Core/Sockets/IPAddress.cpp \
    ../../../../lib/smartfox/Core/Sockets/TCPClient.cpp \
    ../../../../lib/smartfox/Core/Sockets/TCPSocketLayer.cpp \
    ../../../../lib/smartfox/Core/Sockets/UDPClient.cpp \
    ../../../../lib/smartfox/Core/Sockets/UDPSocketLayer.cpp \
    ../../../../lib/smartfox/Core/BaseEvent.cpp \
    ../../../../lib/smartfox/Core/PacketHeader.cpp \
    ../../../../lib/smartfox/Core/SFSBuddyEvent.cpp \
    ../../../../lib/smartfox/Core/SFSEvent.cpp \
    ../../../../lib/smartfox/Core/SFSIOHandler.cpp \
    ../../../../lib/smartfox/Core/SFSProtocolCodec.cpp \
    ../../../../lib/smartfox/Core/ThreadManager.cpp \
    ../../../../lib/smartfox/Entities/Data/SFSArray.cpp \
    ../../../../lib/smartfox/Entities/Data/SFSDataWrapper.cpp \
    ../../../../lib/smartfox/Entities/Data/SFSObject.cpp \
    ../../../../lib/smartfox/Entities/Invitation/SFSInvitation.cpp \
    ../../../../lib/smartfox/Entities/Managers/SFSBuddyManager.cpp \
    ../../../../lib/smartfox/Entities/Managers/SFSGlobalUserManager.cpp \
    ../../../../lib/smartfox/Entities/Managers/SFSRoomManager.cpp \
    ../../../../lib/smartfox/Entities/Managers/SFSUserManager.cpp \
    ../../../../lib/smartfox/Entities/Match/BoolMatch.cpp \
    ../../../../lib/smartfox/Entities/Match/LogicOperator.cpp \
    ../../../../lib/smartfox/Entities/Match/MatchExpression.cpp \
    ../../../../lib/smartfox/Entities/Match/NumberMatch.cpp \
    ../../../../lib/smartfox/Entities/Match/RoomProperties.cpp \
    ../../../../lib/smartfox/Entities/Match/StringMatch.cpp \
    ../../../../lib/smartfox/Entities/Match/UserProperties.cpp \
    ../../../../lib/smartfox/Entities/Variables/ReservedBuddyVariables.cpp \
    ../../../../lib/smartfox/Entities/Variables/ReservedRoomVariables.cpp \
    ../../../../lib/smartfox/Entities/Variables/SFSBuddyVariable.cpp \
    ../../../../lib/smartfox/Entities/Variables/SFSRoomVariable.cpp \
    ../../../../lib/smartfox/Entities/Variables/SFSUserVariable.cpp \
    ../../../../lib/smartfox/Entities/SFSBuddy.cpp \
    ../../../../lib/smartfox/Entities/SFSConstants.cpp \
    ../../../../lib/smartfox/Entities/SFSRoom.cpp \
    ../../../../lib/smartfox/Entities/SFSUser.cpp \
    ../../../../lib/smartfox/Exceptions/SFSCodecError.cpp \
    ../../../../lib/smartfox/Exceptions/SFSError.cpp \
    ../../../../lib/smartfox/Exceptions/SFSValidationError.cpp \
    ../../../../lib/smartfox/FSM/FiniteStateMachine.cpp \
    ../../../../lib/smartfox/FSM/FSMState.cpp \
    ../../../../lib/smartfox/Http/SFSWebClient.cpp \
    ../../../../lib/smartfox/Logging/Logger.cpp \
    ../../../../lib/smartfox/Logging/LoggerEvent.cpp \
    ../../../../lib/smartfox/Protocol/Serialization/DefaultObjectDumpFormatter.cpp \
    ../../../../lib/smartfox/Protocol/Serialization/DefaultSFSDataSerializer.cpp \
    ../../../../lib/smartfox/Requests/Buddylist/AddBuddyRequest.cpp \
    ../../../../lib/smartfox/Requests/Buddylist/BlockBuddyRequest.cpp \
    ../../../../lib/smartfox/Requests/Buddylist/BuddyMessageRequest.cpp \
    ../../../../lib/smartfox/Requests/Buddylist/GoOnlineRequest.cpp \
    ../../../../lib/smartfox/Requests/Buddylist/InitBuddyListRequest.cpp \
    ../../../../lib/smartfox/Requests/Buddylist/RemoveBuddyRequest.cpp \
    ../../../../lib/smartfox/Requests/Buddylist/SetBuddyVariablesRequest.cpp \
    ../../../../lib/smartfox/Requests/Game/CreateSFSGameRequest.cpp \
    ../../../../lib/smartfox/Requests/Game/InvitationReplyRequest.cpp \
    ../../../../lib/smartfox/Requests/Game/InviteUsersRequest.cpp \
    ../../../../lib/smartfox/Requests/Game/QuickGameJoinRequest.cpp \
    ../../../../lib/smartfox/Requests/Game/SFSGameSettings.cpp \
    ../../../../lib/smartfox/Requests/AdminMessageRequest.cpp \
    ../../../../lib/smartfox/Requests/BanUserRequest.cpp \
    ../../../../lib/smartfox/Requests/BaseRequest.cpp \
    ../../../../lib/smartfox/Requests/ChangeRoomCapacityRequest.cpp \
    ../../../../lib/smartfox/Requests/ChangeRoomNameRequest.cpp \
    ../../../../lib/smartfox/Requests/ChangeRoomPasswordStateRequest.cpp \
    ../../../../lib/smartfox/Requests/CreateRoomRequest.cpp \
    ../../../../lib/smartfox/Requests/ExtensionRequest.cpp \
    ../../../../lib/smartfox/Requests/FindRoomsRequest.cpp \
    ../../../../lib/smartfox/Requests/FindUsersRequest.cpp \
    ../../../../lib/smartfox/Requests/GenericMessageRequest.cpp \
    ../../../../lib/smartfox/Requests/HandshakeRequest.cpp \
    ../../../../lib/smartfox/Requests/JoinRoomRequest.cpp \
    ../../../../lib/smartfox/Requests/KickUserRequest.cpp \
    ../../../../lib/smartfox/Requests/LeaveRoomRequest.cpp \
    ../../../../lib/smartfox/Requests/LoginRequest.cpp \
    ../../../../lib/smartfox/Requests/LogoutRequest.cpp \
    ../../../../lib/smartfox/Requests/ManualDisconnectionRequest.cpp \
    ../../../../lib/smartfox/Requests/MessageRecipientMode.cpp \
    ../../../../lib/smartfox/Requests/ModeratorMessageRequest.cpp \
    ../../../../lib/smartfox/Requests/ObjectMessageRequest.cpp \
    ../../../../lib/smartfox/Requests/PingPongRequest.cpp \
    ../../../../lib/smartfox/Requests/PlayerToSpectatorRequest.cpp \
    ../../../../lib/smartfox/Requests/PrivateMessageRequest.cpp \
    ../../../../lib/smartfox/Requests/PublicMessageRequest.cpp \
    ../../../../lib/smartfox/Requests/RoomEvents.cpp \
    ../../../../lib/smartfox/Requests/RoomExtension.cpp \
    ../../../../lib/smartfox/Requests/RoomPermissions.cpp \
    ../../../../lib/smartfox/Requests/RoomSettings.cpp \
    ../../../../lib/smartfox/Requests/SetRoomVariablesRequest.cpp \
    ../../../../lib/smartfox/Requests/SetUserVariablesRequest.cpp \
    ../../../../lib/smartfox/Requests/SpectatorToPlayerRequest.cpp \
    ../../../../lib/smartfox/Requests/SubscribeRoomGroupRequest.cpp \
    ../../../../lib/smartfox/Requests/UnsubscribeRoomGroupRequest.cpp \
    ../../../../lib/smartfox/Util/md5/md5.c \
    ../../../../lib/smartfox/Util/ByteArray.cpp \
    ../../../../lib/smartfox/Util/ClientDisconnectionReason.cpp \
    ../../../../lib/smartfox/Util/ConfigData.cpp \
    ../../../../lib/smartfox/Util/ConfigLoader.cpp \
    ../../../../lib/smartfox/Util/EventDispatcher.cpp \
    ../../../../lib/smartfox/Util/LagMonitor.cpp \
    ../../../../lib/smartfox/Util/SFSErrorCodes.cpp \
    ../../../../lib/smartfox/Util/XMLParser/XMLNode.cpp \
    ../../../../lib/smartfox/Util/XMLParser/XMLNodeList.cpp \
    ../../../../lib/smartfox/Util/XMLParser/XMLNodeValue.cpp \
    ../../../../lib/smartfox/Util/XMLParser/XMLObject.cpp \
    ../../../../lib/smartfox/Util/XMLParser/XMLParser.cpp

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

