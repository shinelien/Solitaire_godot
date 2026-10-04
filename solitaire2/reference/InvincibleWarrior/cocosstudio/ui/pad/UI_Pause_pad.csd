<GameFile>
  <PropertyGroup Name="UI_Pause_pad" Type="Layer" ID="ddeb0284-a2e0-4870-a8d4-0fdf8a556fec" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="100" Speed="1.0000" ActivedAnimationName="Start">
        <Timeline ActionTag="885635984" Property="Alpha">
          <IntFrame FrameIndex="0" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="399398009" Property="ActionValue">
          <InnerActionFrame FrameIndex="0" Tween="False" InnerActionType="LoopAction" CurrentAniamtionName="Start3" SingleFrameIndex="0" />
          <InnerActionFrame FrameIndex="100" Tween="False" InnerActionType="NoLoopAction" CurrentAniamtionName="-- ALL --" SingleFrameIndex="0" />
        </Timeline>
        <Timeline ActionTag="399398009" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-1175996688" Property="Alpha">
          <IntFrame FrameIndex="5" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="20" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="90">
          <RenderColor A="255" R="255" G="255" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="273" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="panel_pause" ActionTag="981607174" Tag="51964" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TopMargin="-142.4880" BottomMargin="-142.4880" TouchEnable="True" ClipAble="False" BackColorAlpha="229" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1724.9761" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="720.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.1979" />
            <SingleColor A="255" R="42" G="45" B="53" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Node_8" ActionTag="-1308411896" Tag="52345" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="720.0000" BottomMargin="720.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="panel_1" ActionTag="536249771" Tag="52359" IconVisible="False" LeftMargin="-540.0000" RightMargin="-540.0000" TopMargin="-960.0000" BottomMargin="-960.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" LeftEage="409" RightEage="409" TopEage="728" BottomEage="728" Scale9OriginX="-409" Scale9OriginY="-728" Scale9Width="818" Scale9Height="1456" ctype="PanelObjectData">
                <Size X="1080.0000" Y="1920.0000" />
                <Children>
                  <AbstractNodeData Name="Node_1" ActionTag="885635984" Tag="52360" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="940.8000" BottomMargin="979.2000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_1" ActionTag="690122307" Tag="52361" IconVisible="False" LeftMargin="-300.0000" RightMargin="-300.0000" TopMargin="-350.0000" BottomMargin="-350.0000" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="90" BottomEage="90" Scale9OriginX="90" Scale9OriginY="90" Scale9Width="207" Scale9Height="296" ctype="ImageViewObjectData">
                        <Size X="600.0000" Y="700.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_bg0.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="540.0000" Y="979.2000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5100" />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_pauseTitle1" ActionTag="-726763548" Tag="52362" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="460.0000" RightMargin="460.0000" TopMargin="651.2001" BottomMargin="1188.7999" FontSize="80" LabelText="暂停" ShadowOffsetX="0.0000" ShadowOffsetY="2.0000" ctype="TextObjectData">
                    <Size X="160.0000" Y="80.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="540.0000" Y="1228.7999" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.6400" />
                    <PreSize X="0.1481" Y="0.0417" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="105" G="68" B="27" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_AD" Visible="False" ActionTag="1382531944" VisibleForFrame="False" Tag="52363" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="160.0000" RightMargin="160.0000" TopMargin="499.2000" BottomMargin="660.8000" Scale9Enable="True" Scale9Width="3" Scale9Height="3" ctype="ImageViewObjectData">
                    <Size X="760.0000" Y="760.0000" />
                    <Children>
                      <AbstractNodeData Name="FileNode_6" ActionTag="399398009" Tag="52364" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="402.8000" RightMargin="357.2000" TopMargin="440.8000" BottomMargin="319.2000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position X="402.8000" Y="319.2000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5300" Y="0.4200" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="ui/Animation/NodeBox.csd" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_getAD" ActionTag="689312201" Tag="52369" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="160.0000" RightMargin="160.0000" TopMargin="505.0000" BottomMargin="125.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="100" RightEage="100" TopEage="46" BottomEage="46" Scale9OriginX="-100" Scale9OriginY="-46" Scale9Width="200" Scale9Height="92" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="440.0000" Y="130.0000" />
                        <Children>
                          <AbstractNodeData Name="Text_get" ActionTag="-1030987137" Tag="52370" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="192.0000" RightMargin="148.0000" TopMargin="34.8000" BottomMargin="45.2000" FontSize="50" LabelText="Free" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="100.0000" Y="50.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="242.0000" Y="70.2000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5500" Y="0.5400" />
                            <PreSize X="0.2273" Y="0.3846" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="ui_Videoplayer_1" ActionTag="99546659" Tag="52371" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="32.0000" RightMargin="296.0000" TopMargin="5.1000" BottomMargin="12.9000" ctype="SpriteObjectData">
                            <Size X="112.0000" Y="112.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="88.0000" Y="68.9000" />
                            <Scale ScaleX="0.6000" ScaleY="0.6000" />
                            <CColor A="255" R="255" G="250" B="157" />
                            <PrePosition X="0.2000" Y="0.5300" />
                            <PreSize X="0.2545" Y="0.8615" />
                            <FileData Type="PlistSubImage" Path="btn1_ad0.png" Plist="ui1.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="380.0000" Y="190.0000" />
                        <Scale ScaleX="1.3000" ScaleY="1.3000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.2500" />
                        <PreSize X="0.5789" Y="0.1711" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="BitmapFontLabel_1" ActionTag="716172399" Tag="52372" RotationSkewY="-0.0035" IconVisible="False" LeftMargin="290.4240" RightMargin="236.5760" TopMargin="-45.3053" BottomMargin="707.3053" LabelText="+100" ctype="TextBMFontObjectData">
                        <Size X="233.0000" Y="98.0000" />
                        <Children>
                          <AbstractNodeData Name="FileNode_1" ActionTag="-1906673531" Tag="52373" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-46.6000" RightMargin="279.6000" TopMargin="48.0200" BottomMargin="49.9800" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <AnchorPoint />
                            <Position X="-46.6000" Y="49.9800" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="-0.2000" Y="0.5100" />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Normal" Path="ui/Animation/Node_currency.csd" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="406.9240" Y="756.3053" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5354" Y="0.9951" />
                        <PreSize X="0.3066" Y="0.1289" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font/Wintips.fnt" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position X="540.0000" Y="1420.8000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.7400" />
                    <PreSize X="0.7037" Y="0.3958" />
                    <FileData Type="PlistSubImage" Path="Challenge_Challenge3.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_eff" ActionTag="1149276640" Tag="52383" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="290.0000" RightMargin="290.0000" TopMargin="918.2000" BottomMargin="879.8000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="90" RightEage="90" Scale9OriginX="90" Scale9Width="91" Scale9Height="122" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="500.0000" Y="122.0000" />
                    <Children>
                      <AbstractNodeData Name="text_effTips" ActionTag="736507455" Tag="52384" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="38.8500" RightMargin="371.1500" TopMargin="38.5000" BottomMargin="38.5000" FontSize="45" LabelText="音效" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="90.0000" Y="45.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="38.8500" Y="61.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.0777" Y="0.5000" />
                        <PreSize X="0.1800" Y="0.3689" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_effTips" ActionTag="-2033029954" Tag="52385" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="282.0000" RightMargin="30.0000" TopMargin="26.5000" BottomMargin="26.5000" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="158" Scale9Height="47" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="188.0000" Y="69.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="470.0000" Y="61.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.9400" Y="0.5000" />
                        <PreSize X="0.3760" Y="0.5656" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="ui_switch1.png" Plist="ui1.plist" />
                        <PressedFileData Type="PlistSubImage" Path="ui_switch0.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_switch0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="540.0000" Y="940.8000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.4900" />
                    <PreSize X="0.4630" Y="0.0635" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_blue0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_music" ActionTag="-1691145568" Tag="52386" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="290.0000" RightMargin="290.0000" TopMargin="783.8000" BottomMargin="1014.2000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="90" RightEage="90" Scale9OriginX="90" Scale9Width="91" Scale9Height="122" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="500.0000" Y="122.0000" />
                    <Children>
                      <AbstractNodeData Name="text_music" ActionTag="-2036474773" Tag="52387" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="40.0000" RightMargin="370.0000" TopMargin="38.5000" BottomMargin="38.5000" FontSize="45" LabelText="音乐" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="90.0000" Y="45.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="40.0000" Y="61.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.0800" Y="0.5000" />
                        <PreSize X="0.1800" Y="0.3689" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_MusicTips" ActionTag="-1191592122" Tag="52388" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="282.0000" RightMargin="30.0000" TopMargin="26.5000" BottomMargin="26.5000" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="158" Scale9Height="47" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="188.0000" Y="69.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="470.0000" Y="61.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.9400" Y="0.5000" />
                        <PreSize X="0.3760" Y="0.5656" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="ui_switch1.png" Plist="ui1.plist" />
                        <PressedFileData Type="PlistSubImage" Path="ui_switch0.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_switch0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="540.0000" Y="1075.2000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5600" />
                    <PreSize X="0.4630" Y="0.0635" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_blue0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="img_pause" ActionTag="-1175996688" Alpha="0" Tag="52389" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-1687.8134" RightMargin="2260.4507" TopMargin="469.8170" BottomMargin="1021.2009" LeftEage="7" RightEage="7" TopEage="21" BottomEage="21" Scale9OriginX="7" Scale9OriginY="21" Scale9Width="10" Scale9Height="23" ctype="ImageViewObjectData">
                    <Size X="507.3625" Y="428.9821" />
                    <Children>
                      <AbstractNodeData Name="Node_root" ActionTag="1362386733" Tag="52390" IconVisible="True" PositionPercentXEnabled="True" LeftMargin="253.6812" RightMargin="253.6812" TopMargin="-45.7178" BottomMargin="474.6999" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position X="253.6812" Y="474.6999" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="1.1066" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_pause_close" Visible="False" ActionTag="1749333183" Tag="52391" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-1875.5854" RightMargin="2062.9104" TopMargin="-121.3242" BottomMargin="302.8534" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="320.0376" Y="247.4529" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-1715.5667" Y="426.5798" />
                        <Scale ScaleX="0.8000" ScaleY="0.8000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-3.3813" Y="0.9944" />
                        <PreSize X="0.6308" Y="0.5768" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-1434.1321" Y="1235.6919" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="-1.3279" Y="0.6436" />
                    <PreSize X="0.4698" Y="0.2234" />
                    <FileData Type="PlistSubImage" Path="ui_pausebg1.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_pause_continue" ActionTag="2139780574" Tag="52392" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="365.0000" RightMargin="365.0000" TopMargin="1091.0000" BottomMargin="707.0000" TouchEnable="True" FontSize="14" LeftEage="100" RightEage="100" TopEage="35" BottomEage="35" Scale9OriginX="100" Scale9OriginY="35" Scale9Width="71" Scale9Height="52" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="350.0000" Y="122.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_continue" ActionTag="1964061330" Tag="52393" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="75.0000" RightMargin="75.0000" TopMargin="33.5600" BottomMargin="38.4400" FontSize="50" LabelText="继续游戏" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="200.0000" Y="50.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="175.0000" Y="63.4400" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5200" />
                        <PreSize X="0.5714" Y="0.4098" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="540.0000" Y="768.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.4000" />
                    <PreSize X="0.3241" Y="0.0635" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_2" Visible="False" ActionTag="-231352160" VisibleForFrame="False" Tag="52394" IconVisible="False" LeftMargin="355.8265" RightMargin="245.7351" TopMargin="772.0221" BottomMargin="980.5507" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="478.4384" Y="167.4273" />
                    <Children>
                      <AbstractNodeData Name="Text_1_0" ActionTag="-1042401220" Tag="52395" IconVisible="False" LeftMargin="162.2387" RightMargin="166.1997" TopMargin="55.5178" BottomMargin="51.9095" FontSize="60" LabelText="$6.99" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="150.0000" Y="60.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="237.2387" Y="81.9095" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="26" G="26" B="26" />
                        <PrePosition X="0.4959" Y="0.4892" />
                        <PreSize X="0.3135" Y="0.3584" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="595.0457" Y="1064.2643" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5510" Y="0.5543" />
                    <PreSize X="0.4430" Y="0.0872" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_3" Visible="False" ActionTag="209766926" VisibleForFrame="False" Tag="52396" IconVisible="False" LeftMargin="476.3417" RightMargin="363.6583" TopMargin="356.7238" BottomMargin="1503.2762" FontSize="60" LabelText="超级礼包" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="240.0000" Y="60.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="596.3417" Y="1533.2762" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5522" Y="0.7986" />
                    <PreSize X="0.2222" Y="0.0313" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_3_0" Visible="False" ActionTag="348174139" VisibleForFrame="False" Tag="52397" IconVisible="False" LeftMargin="467.2606" RightMargin="372.7394" TopMargin="604.1421" BottomMargin="1255.8579" FontSize="60" LabelText="移除广告" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="240.0000" Y="60.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="587.2606" Y="1285.8579" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5438" Y="0.6697" />
                    <PreSize X="0.2222" Y="0.0313" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <SingleColor A="255" R="0" G="0" B="0" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="540.0000" Y="720.0000" />
            <Scale ScaleX="0.7000" ScaleY="0.7000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>