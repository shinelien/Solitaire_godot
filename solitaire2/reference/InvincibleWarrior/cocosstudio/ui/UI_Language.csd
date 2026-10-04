<GameFile>
  <PropertyGroup Name="UI_Language" Type="Layer" ID="b332ae55-e651-4760-a322-5268429b57ad" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="25" Speed="1.6667" ActivedAnimationName="Start">
        <Timeline ActionTag="720540606" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="25" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="2138846145" Property="Alpha">
          <IntFrame FrameIndex="6" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="12" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="1494190782" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.9000" Y="0.9000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1494190782" Property="Alpha">
          <IntFrame FrameIndex="3" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="10" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="255" G="255" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="273" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
          <AbstractNodeData Name="Panel_1" ActionTag="720540606" Alpha="0" Tag="7383" IconVisible="False" LeftMargin="0.0010" RightMargin="-0.0010" TopMargin="-779.9993" BottomMargin="-300.0007" TouchEnable="True" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="3000.0000" />
            <AnchorPoint />
            <Position X="0.0010" Y="-300.0007" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0000" Y="-0.1563" />
            <PreSize X="1.0000" Y="1.5625" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_set" ActionTag="-1429070927" Tag="292" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="0.0002" RightMargin="-0.0002" TopMargin="0.0007" BottomMargin="-0.0007" TouchEnable="True" ClipAble="False" BackColorAlpha="153" ColorAngle="90.0000" LeftEage="409" RightEage="409" TopEage="728" BottomEage="728" Scale9OriginX="-409" Scale9OriginY="-728" Scale9Width="818" Scale9Height="1456" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1920.0000" />
            <Children>
              <AbstractNodeData Name="Panel_out" ActionTag="784939522" Tag="599" RotationSkewX="-0.0013" RotationSkewY="-0.0009" IconVisible="False" LeftMargin="-38.9072" RightMargin="-5.1846" TopMargin="-125.6335" BottomMargin="-154.6050" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="1124.0918" Y="2200.2385" />
                <AnchorPoint />
                <Position X="-38.9072" Y="-154.6050" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="-0.0360" Y="-0.0805" />
                <PreSize X="1.0408" Y="1.1460" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_2" ActionTag="1494190782" Alpha="0" Tag="695" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="864.0000" BottomMargin="1056.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_7" ActionTag="2138846145" Alpha="0" Tag="696" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-510.1604" RightMargin="-510.1604" TopMargin="-720.0000" BottomMargin="-461.4835" Scale9Enable="True" LeftEage="70" RightEage="70" TopEage="70" BottomEage="134" Scale9OriginX="70" Scale9OriginY="70" Scale9Width="156" Scale9Height="201" ctype="ImageViewObjectData">
                    <Size X="1020.3208" Y="1181.4835" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position Y="720.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.4000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="main_table1.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_2" ActionTag="1341241042" Tag="19527" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-473.0000" RightMargin="-473.0000" TopMargin="-685.0300" BottomMargin="-826.9700" LeftEage="25" RightEage="25" TopEage="45" BottomEage="45" Scale9OriginX="25" Scale9OriginY="45" Scale9Width="27" Scale9Height="47" ctype="ImageViewObjectData">
                    <Size X="946.0000" Y="1512.0000" />
                    <AnchorPoint ScaleX="0.5000" />
                    <Position Y="-826.9700" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="198" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_ho0.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Panel_3" ActionTag="350833903" Tag="19412" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-473.0000" RightMargin="-473.0000" TopMargin="-685.0281" BottomMargin="-826.9719" TouchEnable="True" ClipAble="True" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                    <Size X="946.0000" Y="1512.0000" />
                    <Children>
                      <AbstractNodeData Name="BG" ActionTag="-1575126165" Tag="13612" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="946.0000" TopMargin="1512.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.6667" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="ui/Node_wenli2.csd" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="biankuang1_1" ActionTag="22152716" Tag="19525" IconVisible="False" LeftMargin="58.0000" RightMargin="842.0000" TopMargin="58.0000" BottomMargin="1408.0000" ctype="SpriteObjectData">
                        <Size X="46.0000" Y="46.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="81.0000" Y="1431.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.0856" Y="0.9464" />
                        <PreSize X="0.0486" Y="0.0304" />
                        <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="biankuang1_1_0" ActionTag="74079078" Tag="19526" IconVisible="False" LeftMargin="842.0000" RightMargin="58.0000" TopMargin="58.0000" BottomMargin="1408.0000" FlipX="True" ctype="SpriteObjectData">
                        <Size X="46.0000" Y="46.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="865.0000" Y="1431.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.9144" Y="0.9464" />
                        <PreSize X="0.0486" Y="0.0304" />
                        <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" />
                    <Position Y="-826.9719" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <SingleColor A="255" R="150" G="200" B="255" />
                    <FirstColor A="255" R="150" G="200" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_" ActionTag="363270205" Tag="2568" IconVisible="False" LeftMargin="-50.0001" RightMargin="-49.9999" TopMargin="-651.0000" BottomMargin="601.0000" FontSize="50" LabelText="语言" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="100.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-0.0001" Y="626.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="105" G="68" B="27" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_5" ActionTag="1699435630" Tag="2589" IconVisible="True" PositionPercentXEnabled="True" TopMargin="-388.0000" BottomMargin="388.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Button_1_0_0_1_0" ActionTag="-347452914" Tag="20343" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-400.0000" RightMargin="-400.0000" TopMargin="-55.9896" BottomMargin="-68.0104" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="64" RightEage="64" TopEage="11" BottomEage="11" Scale9OriginX="64" Scale9OriginY="11" Scale9Width="6" Scale9Height="102" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="800.0000" Y="124.0000" />
                        <Children>
                          <AbstractNodeData Name="Button_dyy" ActionTag="102320208" Tag="1" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="599.4390" RightMargin="38.1591" TopMargin="27.3748" BottomMargin="24.8452" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="162.4020" Y="71.7800" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="680.6400" Y="60.7352" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.8508" Y="0.4898" />
                            <PreSize X="0.2030" Y="0.5789" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_1" ActionTag="378347777" Tag="101" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="59.9200" RightMargin="644.0800" TopMargin="36.7352" BottomMargin="39.2648" FontSize="48" LabelText="简体" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="96.0000" Y="48.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="107.9200" Y="63.2648" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.1349" Y="0.5102" />
                            <PreSize X="0.1200" Y="0.3871" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-6.0104" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="Ui_settingbtn0.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_1_0_0_1_0_0" ActionTag="126975927" Tag="20543" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-400.0000" RightMargin="-400.0000" TopMargin="98.7725" BottomMargin="-222.7725" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="64" RightEage="64" TopEage="11" BottomEage="11" Scale9OriginX="64" Scale9OriginY="11" Scale9Width="6" Scale9Height="102" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="800.0000" Y="124.0000" />
                        <Children>
                          <AbstractNodeData Name="Button_dyy" ActionTag="113936236" Tag="2" IconVisible="False" LeftMargin="705.0001" RightMargin="34.9999" TopMargin="56.0000" BottomMargin="28.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="60.0000" Y="40.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="735.0001" Y="48.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.9188" Y="0.3871" />
                            <PreSize X="0.0750" Y="0.3226" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_1" ActionTag="-1126041255" Tag="103" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="59.9200" RightMargin="644.0800" TopMargin="38.0000" BottomMargin="38.0000" FontSize="48" LabelText="繁体" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="96.0000" Y="48.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="107.9200" Y="62.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.1349" Y="0.5000" />
                            <PreSize X="0.1200" Y="0.3871" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-160.7725" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="Ui_settingbtn0.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_1_0_0_1_0_0_0" ActionTag="-475680390" Tag="20545" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-400.0000" RightMargin="-400.0000" TopMargin="255.5765" BottomMargin="-379.5765" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="64" RightEage="64" TopEage="11" BottomEage="11" Scale9OriginX="64" Scale9OriginY="11" Scale9Width="6" Scale9Height="102" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="800.0000" Y="124.0000" />
                        <Children>
                          <AbstractNodeData Name="Button_dyy" ActionTag="965097065" Tag="3" IconVisible="False" LeftMargin="646.3549" RightMargin="40.8617" TopMargin="25.4236" BottomMargin="32.1847" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="112.7834" Y="66.3917" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="702.7466" Y="65.3806" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.8784" Y="0.5273" />
                            <PreSize X="0.1410" Y="0.5354" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_1" ActionTag="-2110659918" Tag="105" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="352.0000" RightMargin="352.0000" TopMargin="38.0000" BottomMargin="38.0000" FontSize="48" LabelText="英语" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="96.0000" Y="48.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="400.0000" Y="62.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.1200" Y="0.3871" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-317.5765" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="Ui_settingbtn0.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_1_0_0_1_0_0_0_0" ActionTag="-1077466593" Tag="20548" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-400.0000" RightMargin="-400.0000" TopMargin="427.4112" BottomMargin="-551.4112" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="64" RightEage="64" TopEage="11" BottomEage="11" Scale9OriginX="64" Scale9OriginY="11" Scale9Width="6" Scale9Height="102" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="800.0000" Y="124.0000" />
                        <Children>
                          <AbstractNodeData Name="Text_1" ActionTag="677175817" Tag="107" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="352.0000" RightMargin="352.0000" TopMargin="38.0000" BottomMargin="38.0000" FontSize="48" LabelText="法语" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="96.0000" Y="48.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="400.0000" Y="62.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.1200" Y="0.3871" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Button_dyy" ActionTag="1411918945" Tag="4" IconVisible="False" LeftMargin="555.0737" RightMargin="61.0551" TopMargin="27.2474" BottomMargin="18.6385" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="183.8712" Y="78.1141" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="647.0093" Y="57.6956" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.8088" Y="0.4653" />
                            <PreSize X="0.2298" Y="0.6300" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-489.4112" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="Ui_settingbtn0.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_1_0_0_1_0_0_0_0_0" ActionTag="651101504" Tag="20551" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-400.0000" RightMargin="-400.0000" TopMargin="619.9855" BottomMargin="-743.9855" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="64" RightEage="64" TopEage="11" BottomEage="11" Scale9OriginX="64" Scale9OriginY="11" Scale9Width="6" Scale9Height="102" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="800.0000" Y="124.0000" />
                        <Children>
                          <AbstractNodeData Name="Text_1" ActionTag="-782167483" Tag="109" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="352.0000" RightMargin="352.0000" TopMargin="38.0000" BottomMargin="38.0000" FontSize="48" LabelText="德语" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="96.0000" Y="48.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="400.0000" Y="62.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.1200" Y="0.3871" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Button_dyy" ActionTag="1209667617" Tag="5" IconVisible="False" LeftMargin="575.4150" RightMargin="46.1272" TopMargin="12.4185" BottomMargin="27.1598" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="178.4577" Y="84.4217" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="664.6439" Y="69.3707" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.8308" Y="0.5594" />
                            <PreSize X="0.2231" Y="0.6808" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-681.9855" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="Ui_settingbtn0.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_1_0_0_1_0_0_0_0_0_0" ActionTag="107721768" Tag="20554" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-400.0000" RightMargin="-400.0000" TopMargin="790.3953" BottomMargin="-914.3953" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="64" RightEage="64" TopEage="11" BottomEage="11" Scale9OriginX="64" Scale9OriginY="11" Scale9Width="6" Scale9Height="102" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="800.0000" Y="124.0000" />
                        <Children>
                          <AbstractNodeData Name="Button_dyy" ActionTag="-1504942551" Tag="6" IconVisible="False" LeftMargin="591.0528" RightMargin="45.2968" TopMargin="31.5482" BottomMargin="22.8372" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="163.6504" Y="69.6145" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="672.8780" Y="57.6445" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.8411" Y="0.4649" />
                            <PreSize X="0.2046" Y="0.5614" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_1" ActionTag="202709820" Tag="111" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="352.0000" RightMargin="352.0000" TopMargin="38.0000" BottomMargin="38.0000" FontSize="48" LabelText="日语" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="96.0000" Y="48.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="400.0000" Y="62.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.1200" Y="0.3871" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-852.3953" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="Ui_settingbtn0.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_1_0_0_1_0_0_0_0_0_0_0" ActionTag="-656570396" Tag="20557" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-400.0000" RightMargin="-400.0000" TopMargin="970.6761" BottomMargin="-1094.6761" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="64" RightEage="64" TopEage="11" BottomEage="11" Scale9OriginX="64" Scale9OriginY="11" Scale9Width="6" Scale9Height="102" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="800.0000" Y="124.0000" />
                        <Children>
                          <AbstractNodeData Name="Text_1" ActionTag="1822978741" Tag="113" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="352.0000" RightMargin="352.0000" TopMargin="38.0000" BottomMargin="38.0000" FontSize="48" LabelText="韩语" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="96.0000" Y="48.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="400.0000" Y="62.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.1200" Y="0.3871" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Button_dyy" ActionTag="-1684815975" Tag="7" IconVisible="False" LeftMargin="595.9392" RightMargin="74.9606" TopMargin="13.6607" BottomMargin="35.7891" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                            <Size X="129.1002" Y="74.5502" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="660.4893" Y="73.0642" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.8256" Y="0.5892" />
                            <PreSize X="0.1614" Y="0.6012" />
                            <TextColor A="255" R="65" G="65" B="70" />
                            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-1032.6761" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="Ui_settingbtn0.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="Ui_settingbtn1.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="388.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_set_close" ActionTag="-1331393718" Tag="2569" IconVisible="False" LeftMargin="412.4274" RightMargin="-532.4274" TopMargin="-742.6404" BottomMargin="622.6404" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="29" RightEage="29" TopEage="29" BottomEage="29" Scale9OriginX="29" Scale9OriginY="29" Scale9Width="62" Scale9Height="62" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="120.0000" Y="120.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="472.4274" Y="682.6404" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="PlistSubImage" Path="ui_btn_close3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_btn_close2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="1056.0000" />
                <Scale ScaleX="0.9000" ScaleY="0.9000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5500" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="0.0002" Y="-0.0007" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="173" G="216" B="230" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>