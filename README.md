# jpush-harmony-rn-plugin

## 安装方式
### 手动安装

```
git clone https://github.com/jpush/jpush-harmony-rn-plugin  ----下载源码

复制：jpush-harmony-rn-plugin-1.0.0.tgz  到RN项目中

在RN项目中进行引用：
如：
 "dependencies": {
    ...
     "jpush-harmony-rn-plugin": "file:./jpush-harmony-rn-plugin-1.0.0.tgz",
    ...
  }

npm update


在项目中使用：

import { JPushModule } from 'jpush-harmony-rn-plugin';

```

## 方法

|Key | Support | Description |
| --- | ---- | ----------- |
|init()         | harmony |init       | 
|setDebug(d: boolean)       | harmony | 设置debug 模式                     |
|setAppKey(appKey: string)         | harmony |设置极光appkey                             |
|setChannel(channel: string)         | harmony |设置通知channel                             |
|getRegistrationId()       | harmony |获取regID                            |
|setTags(sequence: number, tags: string[]) | harmony |设置tags  |
|addTags(sequence: number, tags: string[]) | harmony |添加tags  |
|deleteTags(sequence: number, tags: string[]) | harmony |删除tags  |
|cleanTags(sequence: number) | harmony |清理tags  |
|getTags(sequence: number, cur: number) | harmony| 获取tags  |
|checkTagBindState(sequence: number, tag: string) | harmony| 查验tags绑定状态  |
|deleteAlias(sequence: number) | harmony |删除alias  |
|getAlias(sequence: number) | harmony |获取alias  |
|stopPush() | harmony |停止push  |
|resumePush() | harmony |恢复Push  |
|isPushStopped() | harmony |获取Push状态：是否停止  |
|setBadgeNumber(sequence: number) | harmony| 设置角标  |

具体API请查验极光API [JPush HarmonyOS API](https://docs.jiguang.cn/jpush/client/HarmonyOS/hmos_api)。

## 回调 ---直接复制即可

```
addListeners() {
    this.registerListener = DeviceEventEmitter.addListener("onRegister", (data) => {
      console.log("RN 监听 注册成功:", data);
    });

    this.connectedListener = DeviceEventEmitter.addListener("onConnected", (data) => {
      console.log("RN 监听 连接成功:", data);
    });

    this.tagOperatorResultListener = DeviceEventEmitter.addListener("onTagOperatorResult", (data) => {
      console.log("RN 监听 标签操作结果:", data);
    });

    this.aliasOperatorResultListener = DeviceEventEmitter.addListener("onAliasOperatorResult", (data) => {
      console.log("RN 监听 别名操作结果:", data);
    });

    this.clickMessageListener = DeviceEventEmitter.addListener("onClickMessage", (data) => {
      console.log("RN 监听 点击消息:", data);
    });

    this.customMessageListener = DeviceEventEmitter.addListener("onCustomMessage", (data) => {
      console.log("RN 监听 自定义消息:", data);
    });

    this.jMessageExtraListener = DeviceEventEmitter.addListener("onJMessageExtra", (data) => {
      console.log("RN 监听 JMessage附加数据:", data);
    });

    this.jMessageVoIPListener = DeviceEventEmitter.addListener("onJMessageVoIP", (data) => {
      console.log("RN 监听 JMessage VoIP 数据:", data);
    });

    this.commandResultListener = DeviceEventEmitter.addListener("onCommandResult", (data) => {
      console.log("RN 监听 命令结果:", data);
    });
  }
```

##  App.tsx 调用示例

```import React from 'react';
import {StyleSheet, Text, View, ScrollView,TouchableOpacity,TouchableHighlight,DeviceEventEmitter,EmitterSubscription} from 'react-native';

// import { picker } from 'react-native-picker';
import { JPushModule } from 'jpush-harmony-rn-plugin';
const styles = StyleSheet.create({
  scrollView: {
    flex: 1,
  },
  container: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'center',
      backgroundColor: '#F5FCFF',
  },
  button: {
      width: 320,
      justifyContent: 'center',
      alignItems: 'center',
      marginTop: 10,
      borderWidth: 1,
      borderColor: '#3e83d7',
      borderRadius: 8,
      backgroundColor: '#3e83d7',
      padding: 10
  },
  buttonText: {
      textAlign: 'center',
      fontSize: 25,
      color: '#ffffff'
  }
});
interface AppProps {}


export default class App extends React.Component {
  registerListener: EmitterSubscription | null = null;
  connectedListener: EmitterSubscription | null = null;
  tagOperatorResultListener: EmitterSubscription | null = null;
  aliasOperatorResultListener: EmitterSubscription | null = null;
  clickMessageListener: EmitterSubscription | null = null;
  customMessageListener: EmitterSubscription | null = null;
  jMessageExtraListener: EmitterSubscription | null = null;
  jMessageVoIPListener: EmitterSubscription | null = null;
  commandResultListener: EmitterSubscription | null = null;
  constructor(props: AppProps) {
    super(props); // 传递空的 props
    JPushModule.setAppKey("b266cd5c8544ba09b23733e3");
    JPushModule.init();
    JPushModule.setDebug(true);
    this.addListeners();
  }

  addListeners() {
    this.registerListener = DeviceEventEmitter.addListener("onRegister", (data) => {
      console.log("RN 监听 注册成功:", data);
    });

    this.connectedListener = DeviceEventEmitter.addListener("onConnected", (data) => {
      console.log("RN 监听 连接成功:", data);
    });

    this.tagOperatorResultListener = DeviceEventEmitter.addListener("onTagOperatorResult", (data) => {
      console.log("RN 监听 标签操作结果:", data);
    });

    this.aliasOperatorResultListener = DeviceEventEmitter.addListener("onAliasOperatorResult", (data) => {
      console.log("RN 监听 别名操作结果:", data);
    });

    this.clickMessageListener = DeviceEventEmitter.addListener("onClickMessage", (data) => {
      console.log("RN 监听 点击消息:", data);
    });

    this.customMessageListener = DeviceEventEmitter.addListener("onCustomMessage", (data) => {
      console.log("RN 监听 自定义消息:", data);
    });

    this.jMessageExtraListener = DeviceEventEmitter.addListener("onJMessageExtra", (data) => {
      console.log("RN 监听 JMessage附加数据:", data);
    });

    this.jMessageVoIPListener = DeviceEventEmitter.addListener("onJMessageVoIP", (data) => {
      console.log("RN 监听 JMessage VoIP 数据:", data);
    });

    this.commandResultListener = DeviceEventEmitter.addListener("onCommandResult", (data) => {
      console.log("RN 监听 命令结果:", data);
    });
  }

  componentWillUnmount() {
    // 移除所有监听器
    if (this.registerListener) this.registerListener.remove();
    if (this.connectedListener) this.connectedListener.remove();
    if (this.tagOperatorResultListener) this.tagOperatorResultListener.remove();
    if (this.aliasOperatorResultListener) this.aliasOperatorResultListener.remove();
    if (this.clickMessageListener) this.clickMessageListener.remove();
    if (this.customMessageListener) this.customMessageListener.remove();
    if (this.jMessageExtraListener) this.jMessageExtraListener.remove();
    if (this.jMessageVoIPListener) this.jMessageVoIPListener.remove();
    if (this.commandResultListener) this.commandResultListener.remove();
  }
  handleSetChannel = async () => {
    try {
      await JPushModule.setChannel('your_channel'); // 替换为实际的 channel
      console.log("RN Channel set");
    } catch (error) {
      console.error("Error setting channel:", error);
    }
  };

  handleGetRegistrationId = async () => {
    try {
      const registrationId = await JPushModule.getRegistrationId();
      console.log("RN getRegistrationId:", registrationId);
    } catch (error) {
      console.error("Error getting registration ID:", error);
    }
  };

  handleSetTags = async () => {
    try {
      await JPushModule.setTags(1, ['tag1', 'tag2']); // 示例标签
      console.log("RN Tags set");
    } catch (error) {
      console.error("Error setting tags:", error);
    }
  };

  handleAddTags = async () => {
    try {
      await JPushModule.addTags(1, ['tag3']);
      console.log("RN Tags added");
    } catch (error) {
      console.error("Error adding tags:", error);
    }
  };

  handleDeleteTags = async () => {
    try {
      await JPushModule.deleteTags(1, ['tag1']);
      console.log("RN Tags deleted");
    } catch (error) {
      console.error("Error deleting tags:", error);
    }
  };

  handleCleanTags = async () => {
    try {
      await JPushModule.cleanTags(1);
      console.log("RN All tags cleaned");
    } catch (error) {
      console.error("Error cleaning tags:", error);
    }
  };

  handleGetTags = async () => {
    try {
      await JPushModule.getTags(1, 0); // 示例参数
      console.log("RN Tags retrieved");
    } catch (error) {
      console.error("Error getting tags:", error);
    }
  };

  handleCheckTagBindState = async () => {
    try {
      await JPushModule.checkTagBindState(1, 'tag1');
      console.log("RN Tag bind state checked");
    } catch (error) {
      console.error("Error checking tag bind state:", error);
    }
  };

  handleSetAlias = async () => {
    try {
      await JPushModule.setAlias(1, 'myAlias');
      console.log("RN Alias set to 'myAlias'");
    } catch (error) {
      console.error("Error setting alias:", error);
    }
  };

  handleDeleteAlias = async () => {
    try {
      await JPushModule.deleteAlias(1);
      console.log("RN Alias deleted");
    } catch (error) {
      console.error("Error deleting alias:", error);
    }
  };

  handleGetAlias = async () => {
    try {
      const alias = await JPushModule.getAlias(1);
      console.log("RN Alias retrieved:", alias);
    } catch (error) {
      console.error("Error getting alias:", error);
    }
  };

  handleStopPush = async () => {
    try {
      await JPushModule.stopPush();
      console.log("RN Push stopped");
    } catch (error) {
      console.error("Error stopping push:", error);
    }
  };

  handleResumePush = async () => {
    try {
      await JPushModule.resumePush();
      console.log("RN Push resumed");
    } catch (error) {
      console.error("Error resuming push:", error);
    }
  };

  handleCheckPushStatus = () => {
    try {
      const isStopped = JPushModule.isPushStopped();
      console.log("RN Is push stopped?:", isStopped);
    } catch (error) {
      console.error("Error checking push status:", error);
    }
  };

  handleSetBadgeNumber = async () => {
    try {
      await JPushModule.setBadgeNumber(1);
      console.log("RN Badge number set");
    } catch (error) {
      console.error("Error setting badge number:", error);
    }
  };

  renderButtons() {
    return (
      <ScrollView style={styles.scrollView}>
      <View style={styles.container}>
       
        <TouchableOpacity style={styles.button} onPress={this.handleSetChannel}>
          <Text style={styles.buttonText}>设置 Channel</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleGetRegistrationId}>
          <Text style={styles.buttonText}>获取注册 ID</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleSetTags}>
          <Text style={styles.buttonText}>设置 Tags</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleAddTags}>
          <Text style={styles.buttonText}>添加 Tags</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleDeleteTags}>
          <Text style={styles.buttonText}>删除 Tags</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleCleanTags}>
          <Text style={styles.buttonText}>清空 Tags</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleGetTags}>
          <Text style={styles.buttonText}>获取 Tags</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleCheckTagBindState}>
          <Text style={styles.buttonText}>检查 Tag 绑定状态</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleSetAlias}>
          <Text style={styles.buttonText}>设置 Alias</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleDeleteAlias}>
          <Text style={styles.buttonText}>删除 Alias</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleGetAlias}>
          <Text style={styles.buttonText}>获取 Alias</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleStopPush}>
          <Text style={styles.buttonText}>停止推送</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleResumePush}>
          <Text style={styles.buttonText}>恢复推送</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleCheckPushStatus}>
          <Text style={styles.buttonText}>检查推送状态</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={this.handleSetBadgeNumber}>
          <Text style={styles.buttonText}>设置角标</Text>
        </TouchableOpacity>
      </View>
      </ScrollView>
    );
  }
  

  render() {
    return (
      <View style={styles.container}>
        {this.renderButtons()}
      </View>
    );
  }
}	
```
## 鸿蒙侧集成请查看 [JPush HarmonyOS 集成](https://docs.jiguang.cn/jpush/client/HarmonyOS/hmos_guide)。

