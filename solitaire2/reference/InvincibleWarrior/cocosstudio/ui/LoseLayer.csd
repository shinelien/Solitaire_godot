<GameFile>
  <PropertyGroup Name="LoseLayer" Type="Layer" ID="9d4d7b75-943a-4655-a237-97fd8a56be04" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="105" Speed="1.0000" ActivedAnimationName="Start">
        <Timeline ActionTag="-570635339" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="1" />
          </IntFrame>
          <IntFrame FrameIndex="35" Tween="False" Value="229" />
        </Timeline>
        <Timeline ActionTag="-1507164765" Property="Scale">
          <ScaleFrame FrameIndex="10" X="0.0001" Y="0.0001">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="2078686187" Property="Scale">
          <ScaleFrame FrameIndex="80" X="0.3000" Y="0.3000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="105" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="2078686187" Property="Alpha">
          <IntFrame FrameIndex="85" Value="0">
            <EasingData Type="8" />
          </IntFrame>
          <IntFrame FrameIndex="95" Tween="False" Value="255" />
        </Timeline>
        <Timeline ActionTag="255100788" Property="Alpha">
          <IntFrame FrameIndex="80" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="95" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="110">
          <RenderColor A="255" R="240" G="248" B="255" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="273" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
          <AbstractNodeData Name="panel_win" ActionTag="-911047298" Tag="276" IconVisible="False" ClipAble="True" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" LeftEage="409" RightEage="409" TopEage="728" BottomEage="728" Scale9OriginX="-409" Scale9OriginY="-728" Scale9Width="818" Scale9Height="1456" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1920.0000" />
            <Children>
              <AbstractNodeData Name="Image_1" ActionTag="-570635339" Alpha="229" Tag="2193" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-0.0002" RightMargin="0.0002" TopMargin="-0.9600" BottomMargin="0.9600" LeftEage="66" RightEage="66" TopEage="106" BottomEage="106" Scale9OriginX="66" Scale9OriginY="106" Scale9Width="68" Scale9Height="111" ctype="ImageViewObjectData">
                <Size X="1080.0000" Y="1920.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="539.9998" Y="960.9600" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5005" />
                <PreSize X="1.0000" Y="1.0000" />
                <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="panel_6" ActionTag="1105523315" Tag="277" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="277.8400" RightMargin="282.1600" TopMargin="725.0000" BottomMargin="725.0000" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="520.0000" Y="470.0000" />
                <Children>
                  <AbstractNodeData Name="Image_5" ActionTag="1232597906" Tag="282" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-1165.8640" RightMargin="1460.8640" TopMargin="17.2571" BottomMargin="257.7429" LeftEage="46" RightEage="46" TopEage="39" BottomEage="39" Scale9OriginX="46" Scale9OriginY="39" Scale9Width="50" Scale9Height="43" ctype="ImageViewObjectData">
                    <Size X="225.0000" Y="195.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-1053.3640" Y="355.2429" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="-2.0257" Y="0.7558" />
                    <PreSize X="0.4327" Y="0.4149" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="537.8400" Y="960.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4980" Y="0.5000" />
                <PreSize X="0.4815" Y="0.2448" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Panel_1" ActionTag="659956775" Tag="1357" IconVisible="False" LeftMargin="55.0012" RightMargin="54.9988" TopMargin="703.0396" BottomMargin="716.9605" TouchEnable="True" ClipAble="False" ComboBoxIndex="1" ColorAngle="90.0000" ctype="PanelObjectData">
                <Size X="970.0000" Y="500.0000" />
                <Children>
                  <AbstractNodeData Name="Text_1" ActionTag="-161952351" Tag="1358" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="149.0000" RightMargin="149.0000" TopMargin="188.0000" BottomMargin="258.0000" FontSize="48" LabelText="你已无牌可动了。在重来试试吧" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="672.0000" Y="54.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="485.0000" Y="285.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="0" />
                    <PrePosition X="0.5000" Y="0.5700" />
                    <PreSize X="0.6928" Y="0.1080" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="540.0012" Y="966.9605" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5036" />
                <PreSize X="0.8981" Y="0.2604" />
                <SingleColor A="255" R="255" G="255" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_winfont" ActionTag="-1507164765" Tag="1721" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="691.2001" BottomMargin="1228.7999" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_6" ActionTag="-430136461" Tag="2451" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-365.0000" RightMargin="-365.0000" TopMargin="-67.0000" BottomMargin="-67.0000" Scale9Enable="True" LeftEage="98" RightEage="98" TopEage="44" BottomEage="44" Scale9OriginX="98" Scale9OriginY="44" Scale9Width="101" Scale9Height="46" ctype="ImageViewObjectData">
                    <Size X="730.0000" Y="134.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_EndBG2.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_1" ActionTag="1814617241" Tag="1754" IconVisible="True" TopMargin="-13.0000" BottomMargin="13.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_title" ActionTag="816625772" Tag="617" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-142.5000" RightMargin="-182.5000" TopMargin="-37.0000" BottomMargin="-37.0000" FontSize="65" LabelText="再接再厉！" ShadowOffsetX="0.0000" ShadowOffsetY="-5.0000" ShadowEnabled="True" ctype="TextObjectData">
                        <Size X="325.0000" Y="74.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="20.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="0" G="0" B="0" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="13.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="1228.7999" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.6400" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn_new" ActionTag="2078686187" Tag="285" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="164.0906" RightMargin="169.9094" TopMargin="1178.2000" BottomMargin="563.8000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="50" BottomEage="50" Scale9OriginX="90" Scale9OriginY="50" Scale9Width="40" Scale9Height="78" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="746.0000" Y="178.0000" />
                <Children>
                  <AbstractNodeData Name="text_new" ActionTag="-1671680129" Tag="286" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="268.0000" RightMargin="268.0000" TopMargin="37.0400" BottomMargin="61.9600" FontSize="70" LabelText="新游戏" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="210.0000" Y="79.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="373.0000" Y="101.4600" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5700" />
                    <PreSize X="0.2815" Y="0.4438" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5039" ScaleY="0.5000" />
                <Position X="540.0000" Y="652.8000" />
                <Scale ScaleX="1.0227" ScaleY="1.0227" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3400" />
                <PreSize X="0.6907" Y="0.0927" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_2_0" ActionTag="255100788" Tag="10583" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="365.0000" RightMargin="365.0000" TopMargin="1370.8000" BottomMargin="449.2000" TouchEnable="True" FontSize="30" ButtonText="重新开始" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="62" Scale9Height="78" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="350.0000" Y="100.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="540.0000" Y="499.2000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2600" />
                <PreSize X="0.3241" Y="0.0521" />
                <TextColor A="255" R="255" G="255" B="255" />
                <DisabledFileData Type="PlistSubImage" Path="ui_btn_S2.png" Plist="ui1.plist" />
                <PressedFileData Type="PlistSubImage" Path="ui_btn_S1.png" Plist="ui1.plist" />
                <NormalFileData Type="PlistSubImage" Path="ui_btn_S0.png" Plist="ui1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>