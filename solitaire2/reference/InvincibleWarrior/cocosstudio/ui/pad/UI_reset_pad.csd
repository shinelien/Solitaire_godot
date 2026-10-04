<GameFile>
  <PropertyGroup Name="UI_reset_pad" Type="Layer" ID="cbffa7cb-fc9c-4866-8cb4-60fc8d14ba2f" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="25" Speed="1.6667" ActivedAnimationName="Start">
        <Timeline ActionTag="-1404418635" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="25" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1850714951" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="4" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="401616621" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="4" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-1429070927" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="2" />
          </IntFrame>
          <IntFrame FrameIndex="20" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1429070927" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="-140.0000">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="255" G="255" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="273" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Text_startTitle" ActionTag="-1400809954" Tag="1350" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-226.3000" RightMargin="1172.3000" TopMargin="-1104.6121" BottomMargin="2487.6121" FontSize="50" LabelText=" سوليتير" ShadowOffsetX="0.0000" ShadowOffsetY="2.0000" ctype="TextObjectData">
            <Size X="134.0000" Y="57.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-159.3000" Y="2516.1121" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1475" Y="1.7473" />
            <PreSize X="0.1241" Y="0.0396" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="105" G="68" B="27" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_1" ActionTag="-1404418635" Alpha="0" Tag="3839" IconVisible="False" LeftMargin="0.0012" RightMargin="-0.0012" TouchEnable="True" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <AnchorPoint />
            <Position X="0.0012" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_reset" ActionTag="-1429070927" Alpha="0" Tag="292" IconVisible="False" PercentWidthEnable="True" PercentWidthEnabled="True" VerticalEdge="TopEdge" TopMargin="-666.3999" BottomMargin="-140.0000" TouchEnable="True" ClipAble="True" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" LeftEage="409" RightEage="409" TopEage="728" BottomEage="728" Scale9OriginX="-409" Scale9OriginY="-728" Scale9Width="818" Scale9Height="1456" ctype="PanelObjectData">
            <Size X="1080.0000" Y="2246.3999" />
            <Children>
              <AbstractNodeData Name="btn_reset_close" ActionTag="-123724584" Tag="4612" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" TopMargin="806.3999" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="-15" Scale9OriginY="-11" Scale9Width="30" Scale9Height="22" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="1080.0000" Y="1440.0000" />
                <AnchorPoint ScaleX="0.5000" />
                <Position X="540.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" />
                <PreSize X="1.0000" Y="0.6410" />
                <TextColor A="255" R="65" G="65" B="70" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Panel_out" ActionTag="-1809875034" Tag="548" IconVisible="False" LeftMargin="264.7021" RightMargin="260.0643" TopMargin="1164.1166" BottomMargin="237.1140" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="555.2336" Y="845.1693" />
                <AnchorPoint />
                <Position X="264.7021" Y="237.1140" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2451" Y="0.1056" />
                <PreSize X="0.5141" Y="0.3762" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="img_reset" ActionTag="1040165131" Tag="293" IconVisible="False" PositionPercentXEnabled="True" TopMargin="806.3997" BottomMargin="0.0002" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="1080.0000" Y="1440.0000" />
                <Children>
                  <AbstractNodeData Name="Node_root" ActionTag="1226776323" Tag="676" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="1622.3760" RightMargin="-542.3760" TopMargin="361.7280" BottomMargin="1078.2720" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="1622.3760" Y="1078.2720" />
                    <Scale ScaleX="1.0000" ScaleY="2.3838" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="1.5022" Y="0.7488" />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_2_0" ActionTag="780007264" Tag="195" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="720.0000" BottomMargin="720.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_6" ActionTag="303624345" Tag="255" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-507.0490" RightMargin="-507.0490" TopMargin="-634.0022" BottomMargin="-923.4379" Scale9Enable="True" LeftEage="97" RightEage="97" TopEage="133" BottomEage="133" Scale9OriginX="97" Scale9OriginY="133" Scale9Width="102" Scale9Height="139" ctype="ImageViewObjectData">
                        <Size X="1014.0981" Y="1557.4401" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                        <Position Y="634.0022" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="main_table1.png" Plist="ui.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg8_1" ActionTag="1545839483" Tag="196" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="579.9916" BottomMargin="-625.9916" ctype="SpriteObjectData">
                        <Size X="46.0000" Y="46.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                        <Position Y="-579.9916" />
                        <Scale ScaleX="0.9465" ScaleY="1.7333" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_1" ActionTag="-1553916071" Tag="197" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-450.0000" TopMargin="-590.0000" BottomMargin="-590.0000" LeftEage="153" RightEage="153" TopEage="389" BottomEage="389" Scale9OriginX="-107" Scale9OriginY="-343" Scale9Width="260" Scale9Height="732" ctype="ImageViewObjectData">
                        <Size X="450.0000" Y="1180.0000" />
                        <Children>
                          <AbstractNodeData Name="Image_3" ActionTag="-858658176" Tag="618" IconVisible="False" LeftMargin="-412.5641" RightMargin="431.5641" TopMargin="23.4994" BottomMargin="1061.5006" FlipX="True" Scale9Enable="True" LeftEage="25" RightEage="230" TopEage="31" BottomEage="31" Scale9OriginX="-184" Scale9OriginY="15" Scale9Width="209" Scale9Height="16" ctype="ImageViewObjectData">
                            <Size X="431.0000" Y="95.0000" />
                            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                            <Position X="18.4359" Y="1109.0006" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="139" G="105" B="20" />
                            <PrePosition X="0.0410" Y="0.9398" />
                            <PreSize X="0.9578" Y="0.0805" />
                            <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Image_1_0" ActionTag="29503889" Tag="199" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" FlipX="True" LeftEage="153" RightEage="153" TopEage="389" BottomEage="389" Scale9OriginX="-107" Scale9OriginY="-343" Scale9Width="260" Scale9Height="732" ctype="ImageViewObjectData">
                            <Size X="450.0000" Y="1180.0000" />
                            <Children>
                              <AbstractNodeData Name="Image_3_0" ActionTag="-839253090" Tag="916" IconVisible="False" LeftMargin="-413.4363" RightMargin="431.4363" TopMargin="23.5001" BottomMargin="1061.4999" FlipX="True" Scale9Enable="True" LeftEage="25" RightEage="230" TopEage="31" BottomEage="31" Scale9OriginX="-184" Scale9OriginY="15" Scale9Width="209" Scale9Height="16" ctype="ImageViewObjectData">
                                <Size X="432.0000" Y="95.0000" />
                                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                                <Position X="18.5637" Y="1108.9999" />
                                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                                <CColor A="255" R="139" G="105" B="20" />
                                <PrePosition X="0.0413" Y="0.9398" />
                                <PreSize X="0.9600" Y="0.0805" />
                                <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                            <Position X="450.0000" Y="590.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="1.0000" Y="0.5000" />
                            <PreSize X="1.0000" Y="1.0000" />
                            <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Image_4" ActionTag="-1804538289" Tag="1472" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="124.0000" RightMargin="-326.0000" TopMargin="33.9994" BottomMargin="1078.0006" Scale9Enable="True" LeftEage="49" RightEage="49" TopEage="22" BottomEage="22" Scale9OriginX="49" Scale9OriginY="22" Scale9Width="53" Scale9Height="24" ctype="ImageViewObjectData">
                            <Size X="652.0000" Y="68.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="450.0000" Y="1112.0006" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="120" G="93" B="60" />
                            <PrePosition X="1.0000" Y="0.9424" />
                            <PreSize X="1.4489" Y="0.0576" />
                            <FileData Type="PlistSubImage" Path="game0_ui3.png" Plist="ui.plist" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="game0_ui0_1" ActionTag="-1040886281" Tag="201" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="165.8942" RightMargin="238.1058" TopMargin="1139.9999" BottomMargin="-5.9999" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5023" />
                            <Position X="189.0000" Y="-5.9999" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.4200" Y="-0.0051" />
                            <PreSize X="0.1022" Y="0.0390" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="game0_ui0_1_0" ActionTag="1516523324" Tag="202" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="687.8942" RightMargin="-283.8942" TopMargin="1140.0000" BottomMargin="-6.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5023" />
                            <Position X="711.0000" Y="-6.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="1.5800" Y="-0.0051" />
                            <PreSize X="0.1022" Y="0.0390" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg1_9_1" ActionTag="968489449" Tag="203" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-44.0000" RightMargin="-44.0000" TopMargin="683.0001" BottomMargin="-799.0001" FlipY="True" ctype="SpriteObjectData">
                        <Size X="88.0000" Y="116.0000" />
                        <AnchorPoint ScaleX="0.5000" />
                        <Position Y="-799.0001" />
                        <Scale ScaleX="10.2962" ScaleY="0.4000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg4_1_0_0_0" ActionTag="368420158" Tag="204" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-283.0000" RightMargin="-283.0000" TopMargin="-420.0000" BottomMargin="380.0000" ctype="SpriteObjectData">
                        <Size X="566.0000" Y="40.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="400.0000" />
                        <Scale ScaleX="1.3361" ScaleY="0.9589" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="game0_uibg4.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg1_9" ActionTag="-691120438" Tag="205" IconVisible="False" LeftMargin="-44.0001" RightMargin="-43.9999" TopMargin="-589.9996" BottomMargin="473.9996" ctype="SpriteObjectData">
                        <Size X="88.0000" Y="116.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                        <Position X="-0.0001" Y="589.9996" />
                        <Scale ScaleX="10.2596" ScaleY="0.3100" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg1_9_0" ActionTag="1632460218" Alpha="178" Tag="206" RotationSkewX="-90.0000" RotationSkewY="-90.0002" IconVisible="False" LeftMargin="361.9952" RightMargin="-449.9952" TopMargin="-711.9991" BottomMargin="595.9991" FlipY="True" ctype="SpriteObjectData">
                        <Size X="88.0000" Y="116.0000" />
                        <AnchorPoint ScaleX="1.0000" />
                        <Position X="449.9952" Y="595.9991" />
                        <Scale ScaleX="15.8649" ScaleY="0.3100" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg1_9_0_0" ActionTag="-1880168077" Alpha="178" Tag="207" RotationSkewX="-90.0000" RotationSkewY="-90.0002" IconVisible="False" LeftMargin="-537.9998" RightMargin="449.9998" TopMargin="-589.9983" BottomMargin="473.9983" ctype="SpriteObjectData">
                        <Size X="88.0000" Y="116.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                        <Position X="-449.9998" Y="589.9983" />
                        <Scale ScaleX="15.8111" ScaleY="0.3100" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg2_3_0" ActionTag="850443141" Tag="208" IconVisible="False" LeftMargin="416.0005" RightMargin="-462.0005" TopMargin="-603.0020" BottomMargin="557.0020" FlipX="True" ctype="SpriteObjectData">
                        <Size X="46.0000" Y="46.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                        <Position X="462.0005" Y="603.0020" />
                        <Scale ScaleX="1.0000" ScaleY="0.9724" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="game0_uibg2_3" ActionTag="-1469682756" Tag="209" IconVisible="False" LeftMargin="-461.9999" RightMargin="415.9999" TopMargin="-603.0007" BottomMargin="557.0007" ctype="SpriteObjectData">
                        <Size X="46.0000" Y="46.0000" />
                        <AnchorPoint ScaleY="1.0000" />
                        <Position X="-461.9999" Y="603.0007" />
                        <Scale ScaleX="1.0000" ScaleY="0.9725" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_2" ActionTag="627416780" Tag="210" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-462.5000" RightMargin="-462.5000" TopMargin="-603.0003" BottomMargin="587.0003" LeftEage="315" RightEage="315" TopEage="5" BottomEage="5" Scale9OriginX="-269" Scale9OriginY="5" Scale9Width="584" Scale9Height="36" ctype="ImageViewObjectData">
                        <Size X="925.0000" Y="16.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="595.0003" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_random_new" ActionTag="-230139527" Tag="3239" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-385.0000" RightMargin="-385.0000" TopMargin="-139.0000" BottomMargin="-19.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="180" RightEage="180" TopEage="30" BottomEage="30" Scale9OriginX="-141" Scale9OriginY="-14" Scale9Width="321" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="770.0000" Y="158.0000" />
                        <Children>
                          <AbstractNodeData Name="text_random_new" ActionTag="-1610674206" Tag="3240" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="275.0000" RightMargin="275.0000" TopMargin="47.5000" BottomMargin="47.5000" FontSize="55" LabelText="困难模式" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="220.0000" Y="63.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="385.0000" Y="79.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.2857" Y="0.3987" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Image_16_0" ActionTag="1686341275" Tag="1409" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="4.0030" RightMargin="-2.0030" TopMargin="154.3600" BottomMargin="-57.3600" Scale9Enable="True" LeftEage="17" RightEage="17" TopEage="19" BottomEage="19" Scale9OriginX="17" Scale9OriginY="19" Scale9Width="734" Scale9Height="23" ctype="ImageViewObjectData">
                            <Size X="768.0000" Y="61.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="388.0030" Y="-26.8600" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5039" Y="-0.1700" />
                            <PreSize X="0.9974" Y="0.3861" />
                            <FileData Type="PlistSubImage" Path="game0_ui1.png" Plist="ui.plist" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_bestScore2" ActionTag="-840357671" Tag="1412" IconVisible="False" LeftMargin="644.3000" RightMargin="11.7000" TopMargin="163.0000" BottomMargin="-45.0000" LabelText="3444" ctype="TextBMFontObjectData">
                            <Size X="114.0000" Y="40.0000" />
                            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                            <Position X="758.3000" Y="-25.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.9848" Y="-0.1582" />
                            <PreSize X="0.1481" Y="0.2532" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num0.fnt" Plist="" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="text_highscore2" ActionTag="-812300918" Tag="252" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="38.5000" RightMargin="511.5000" TopMargin="164.8600" BottomMargin="-46.8600" FontSize="35" LabelText="Highest Score" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="220.0000" Y="40.0000" />
                            <AnchorPoint ScaleY="0.5000" />
                            <Position X="38.5000" Y="-26.8600" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.0500" Y="-0.1700" />
                            <PreSize X="0.2857" Y="0.2532" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="FileNode_GradeHard" ActionTag="-1230563662" Tag="1099" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="777.7000" RightMargin="-7.7000" TopMargin="189.6000" BottomMargin="-31.6000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.6667" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <AnchorPoint />
                            <Position X="777.7000" Y="-31.6000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="1.0100" Y="-0.2000" />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Normal" Path="ui/Grade.csd" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="60.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_O1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_O0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_huo_new" ActionTag="9616402" Tag="3241" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-385.0000" RightMargin="-385.0000" TopMargin="-379.0000" BottomMargin="221.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="180" RightEage="180" TopEage="30" BottomEage="30" Scale9OriginX="-141" Scale9OriginY="-14" Scale9Width="321" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="770.0000" Y="158.0000" />
                        <Children>
                          <AbstractNodeData Name="text_huo_new" ActionTag="63746559" Tag="3242" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="275.0000" RightMargin="275.0000" TopMargin="47.5000" BottomMargin="47.5000" FontSize="55" LabelText="经典模式" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="220.0000" Y="63.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="385.0000" Y="79.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.2857" Y="0.3987" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Image_16" ActionTag="-793879760" Tag="1408" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="4.0000" RightMargin="-2.0000" TopMargin="154.3600" BottomMargin="-57.3600" Scale9Enable="True" LeftEage="17" RightEage="17" TopEage="19" BottomEage="19" Scale9OriginX="17" Scale9OriginY="19" Scale9Width="734" Scale9Height="23" ctype="ImageViewObjectData">
                            <Size X="768.0000" Y="61.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="388.0000" Y="-26.8600" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5039" Y="-0.1700" />
                            <PreSize X="0.9974" Y="0.3861" />
                            <FileData Type="PlistSubImage" Path="game0_ui1.png" Plist="ui.plist" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="text_highscore1" ActionTag="1946253441" Tag="251" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="38.5000" RightMargin="511.5000" TopMargin="164.8600" BottomMargin="-46.8600" FontSize="35" LabelText="Highest Score" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="220.0000" Y="40.0000" />
                            <AnchorPoint ScaleY="0.5000" />
                            <Position X="38.5000" Y="-26.8600" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.0500" Y="-0.1700" />
                            <PreSize X="0.2857" Y="0.2532" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_bestScore1" ActionTag="-1265433070" Tag="1413" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="632.9000" RightMargin="23.1000" TopMargin="162.9998" BottomMargin="-44.9998" LabelText="3444" ctype="TextBMFontObjectData">
                            <Size X="114.0000" Y="40.0000" />
                            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                            <Position X="746.9000" Y="-24.9998" />
                            <Scale ScaleX="0.9000" ScaleY="0.9000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.9700" Y="-0.1582" />
                            <PreSize X="0.1481" Y="0.2532" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num0.fnt" Plist="" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="FileNode_GradeClassic" ActionTag="976538952" Tag="1122" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="777.7000" RightMargin="-7.7000" TopMargin="189.6000" BottomMargin="-31.6000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.6667" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <AnchorPoint />
                            <Position X="777.7000" Y="-31.6000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="1.0100" Y="-0.2000" />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Normal" Path="ui/Grade.csd" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="300.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_O1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_O0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_level" ActionTag="-2002883392" Tag="1160" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-385.0000" RightMargin="-385.0000" TopMargin="101.0000" BottomMargin="-259.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="180" RightEage="180" TopEage="30" BottomEage="30" Scale9OriginX="-141" Scale9OriginY="-14" Scale9Width="321" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="770.0000" Y="158.0000" />
                        <Children>
                          <AbstractNodeData Name="Particle_1" ActionTag="-1850714951" VisibleForFrame="False" Tag="1975" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="154.0000" RightMargin="616.0000" TopMargin="72.1270" BottomMargin="85.8730" ctype="ParticleObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <AnchorPoint />
                            <Position X="154.0000" Y="85.8730" />
                            <Scale ScaleX="0.7000" ScaleY="0.7000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.2000" Y="0.5435" />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Normal" Path="Particicle/Start_BG.plist" Plist="" />
                            <BlendFunc Src="1" Dst="1" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Sprite_tips" ActionTag="475486494" Tag="902" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="723.6000" RightMargin="-15.6000" TopMargin="-26.0200" BottomMargin="113.0200" ctype="SpriteObjectData">
                            <Size X="62.0000" Y="71.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="754.6000" Y="148.5200" />
                            <Scale ScaleX="0.8000" ScaleY="0.8000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.9800" Y="0.9400" />
                            <PreSize X="0.0805" Y="0.4494" />
                            <FileData Type="PlistSubImage" Path="main_tips.png" Plist="ui.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="ui_star0_1" ActionTag="-1092147077" Tag="1974" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="131.0000" RightMargin="593.0000" TopMargin="49.1270" BottomMargin="62.8730" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="154.0000" Y="85.8730" />
                            <Scale ScaleX="0.6000" ScaleY="0.6000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.2000" Y="0.5435" />
                            <PreSize X="0.0597" Y="0.2911" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="text_levelchallenge" ActionTag="-629190027" Tag="1161" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="275.0000" RightMargin="275.0000" TopMargin="47.5000" BottomMargin="47.5000" FontSize="55" LabelText="关卡挑战" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="220.0000" Y="63.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="385.0000" Y="79.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.2857" Y="0.3987" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Image_16_0_0" ActionTag="-607423069" Tag="1976" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="4.0030" RightMargin="-2.0030" TopMargin="155.4720" BottomMargin="-58.4720" Scale9Enable="True" LeftEage="17" RightEage="17" TopEage="19" BottomEage="19" Scale9OriginX="17" Scale9OriginY="19" Scale9Width="734" Scale9Height="23" ctype="ImageViewObjectData">
                            <Size X="768.0000" Y="61.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position X="388.0030" Y="2.5280" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5039" Y="0.0160" />
                            <PreSize X="0.9974" Y="0.3861" />
                            <FileData Type="PlistSubImage" Path="game0_ui1.png" Plist="ui.plist" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="text_totalstarnum" ActionTag="2042508767" Tag="253" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="38.5000" RightMargin="666.5000" TopMargin="164.8600" BottomMargin="-46.8600" FontSize="35" LabelText="Star" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="65.0000" Y="40.0000" />
                            <AnchorPoint ScaleY="0.5000" />
                            <Position X="38.5000" Y="-26.8600" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.0500" Y="-0.1700" />
                            <PreSize X="0.0844" Y="0.2532" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_currentLevelStar" ActionTag="-832930969" Tag="1977" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="700.6000" RightMargin="15.4000" TopMargin="166.4400" BottomMargin="-48.4400" LabelText="20" ctype="TextBMFontObjectData">
                            <Size X="54.0000" Y="40.0000" />
                            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                            <Position X="754.6000" Y="-28.4400" />
                            <Scale ScaleX="0.9000" ScaleY="0.9000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.9800" Y="-0.1800" />
                            <PreSize X="0.0701" Y="0.2532" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num0.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-180.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_O1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_O0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_daily" ActionTag="-1393194577" Tag="3062" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-385.0000" RightMargin="-385.0000" TopMargin="341.0000" BottomMargin="-499.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="180" RightEage="180" TopEage="30" BottomEage="30" Scale9OriginX="-141" Scale9OriginY="-14" Scale9Width="321" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="770.0000" Y="158.0000" />
                        <Children>
                          <AbstractNodeData Name="Particle_1" ActionTag="401616621" VisibleForFrame="False" Tag="3063" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="154.0000" RightMargin="616.0000" TopMargin="83.1870" BottomMargin="74.8130" ctype="ParticleObjectData">
                            <Size X="0.0000" Y="0.0000" />
                            <AnchorPoint />
                            <Position X="154.0000" Y="74.8130" />
                            <Scale ScaleX="0.7000" ScaleY="0.7000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.2000" Y="0.4735" />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Normal" Path="Particicle/Start_BG.plist" Plist="" />
                            <BlendFunc Src="1" Dst="1" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Sprite_dailyTips" ActionTag="-689969342" Tag="3064" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="723.6000" RightMargin="-15.6000" TopMargin="-26.0200" BottomMargin="113.0200" ctype="SpriteObjectData">
                            <Size X="62.0000" Y="71.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="754.6000" Y="148.5200" />
                            <Scale ScaleX="0.8000" ScaleY="0.8000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.9800" Y="0.9400" />
                            <PreSize X="0.0805" Y="0.4494" />
                            <FileData Type="PlistSubImage" Path="main_tips.png" Plist="ui.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="ui_star0_1" ActionTag="1332429670" Tag="3065" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="131.0000" RightMargin="593.0000" TopMargin="51.2600" BottomMargin="60.7400" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="154.0000" Y="83.7400" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.2000" Y="0.5300" />
                            <PreSize X="0.0597" Y="0.2911" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="text_dailyChallenge" ActionTag="-1218772040" Tag="3066" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="275.0000" RightMargin="275.0000" TopMargin="47.5000" BottomMargin="47.5000" FontSize="55" LabelText="每日挑战" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="220.0000" Y="63.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="385.0000" Y="79.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.2857" Y="0.3987" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Image_16_0_0" ActionTag="-1381422213" Tag="3067" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="4.0030" RightMargin="-2.0030" TopMargin="155.4720" BottomMargin="-58.4720" Scale9Enable="True" LeftEage="17" RightEage="17" TopEage="19" BottomEage="19" Scale9OriginX="17" Scale9OriginY="19" Scale9Width="734" Scale9Height="23" ctype="ImageViewObjectData">
                            <Size X="768.0000" Y="61.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                            <Position X="388.0030" Y="2.5280" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5039" Y="0.0160" />
                            <PreSize X="0.9974" Y="0.3861" />
                            <FileData Type="PlistSubImage" Path="game0_ui1.png" Plist="ui.plist" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="text_totalcrownnum" ActionTag="-914189977" Tag="3068" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="38.5000" RightMargin="629.5000" TopMargin="164.8600" BottomMargin="-46.8600" FontSize="35" LabelText="Crown" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="102.0000" Y="40.0000" />
                            <AnchorPoint ScaleY="0.5000" />
                            <Position X="38.5000" Y="-26.8600" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.0500" Y="-0.1700" />
                            <PreSize X="0.1325" Y="0.2532" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_currentDailyCrown1" ActionTag="1131092529" Tag="3069" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="650.7440" RightMargin="102.2560" TopMargin="165.2392" BottomMargin="-47.2392" LabelText="1" ctype="TextBMFontObjectData">
                            <Size X="17.0000" Y="40.0000" />
                            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                            <Position X="667.7440" Y="-27.2392" />
                            <Scale ScaleX="0.9000" ScaleY="0.9000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.8672" Y="-0.1724" />
                            <PreSize X="0.0221" Y="0.2532" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num0.fnt" Plist="" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_3" ActionTag="379225435" Tag="3070" IconVisible="False" LeftMargin="681.6478" RightMargin="76.3522" TopMargin="166.2635" BottomMargin="-53.2635" FontSize="40" LabelText="/" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="12.0000" Y="45.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="687.6478" Y="-30.7635" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.8930" Y="-0.1947" />
                            <PreSize X="0.0156" Y="0.2848" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_currentDailyCrown2" ActionTag="1651944243" Tag="3071" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="700.6000" RightMargin="15.4000" TopMargin="165.2392" BottomMargin="-47.2392" LabelText="22" ctype="TextBMFontObjectData">
                            <Size X="54.0000" Y="40.0000" />
                            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                            <Position X="754.6000" Y="-27.2392" />
                            <Scale ScaleX="0.9000" ScaleY="0.9000" />
                            <CColor A="255" R="96" G="57" B="26" />
                            <PrePosition X="0.9800" Y="-0.1724" />
                            <PreSize X="0.0701" Y="0.2532" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num0.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-420.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_O1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_O0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_cardMode" ActionTag="1467745870" Tag="701" IconVisible="False" LeftMargin="-180.0000" RightMargin="-180.0000" TopMargin="-466.0000" BottomMargin="414.0000" FontSize="45" LabelText="纸牌模式：一张牌" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="360.0000" Y="52.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="440.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="96" G="57" B="26" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_title" ActionTag="586433784" Tag="242" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-90.0000" RightMargin="-90.0000" TopMargin="-548.0002" BottomMargin="496.0002" FontSize="45" LabelText="选择模式" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="180.0000" Y="52.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="522.0002" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_reset_replay" ActionTag="-1793600169" Tag="4618" IconVisible="False" LeftMargin="-409.0000" RightMargin="271.0000" TopMargin="610.0000" BottomMargin="-748.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="51" RightEage="51" TopEage="30" BottomEage="30" Scale9OriginX="-37" Scale9OriginY="-16" Scale9Width="88" Scale9Height="46" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="138.0000" Y="138.0000" />
                        <Children>
                          <AbstractNodeData Name="text_replay" ActionTag="1786904616" VisibleForFrame="False" Tag="4619" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-47.0000" RightMargin="-47.0000" TopMargin="36.0000" BottomMargin="36.0000" FontSize="58" LabelText="重玩本局" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="232.0000" Y="66.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="69.0000" Y="69.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="213" B="164" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="1.6812" Y="0.4783" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_share" ActionTag="-1583118011" Tag="997" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="29.0000" RightMargin="29.0000" TopMargin="137.5800" BottomMargin="-44.5800" FontSize="40" LabelText="分享" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="80.0000" Y="45.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="69.0000" Y="-22.0800" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="197" G="154" B="125" />
                            <PrePosition X="0.5000" Y="-0.1600" />
                            <PreSize X="0.5797" Y="0.3261" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-340.0000" Y="-679.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="ui_btn_share1.png" Plist="ui1.plist" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_share1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_share0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_statistic" ActionTag="-1614099360" Tag="1716" IconVisible="False" LeftMargin="-182.3333" RightMargin="44.3333" TopMargin="609.9998" BottomMargin="-747.9998" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="-1" Scale9OriginY="3" Scale9Width="16" Scale9Height="8" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="138.0000" Y="138.0000" />
                        <Children>
                          <AbstractNodeData Name="Text_statistics" ActionTag="-924425994" Tag="996" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="29.0000" RightMargin="29.0000" TopMargin="137.5800" BottomMargin="-44.5800" FontSize="40" LabelText="胜率" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="80.0000" Y="45.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="69.0000" Y="-22.0800" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="197" G="154" B="125" />
                            <PrePosition X="0.5000" Y="-0.1600" />
                            <PreSize X="0.5797" Y="0.3261" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-113.3333" Y="-678.9998" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_data1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_data0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_rank" ActionTag="1429397772" Tag="1719" IconVisible="False" LeftMargin="44.3333" RightMargin="-182.3333" TopMargin="609.9998" BottomMargin="-747.9998" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="-1" Scale9OriginY="3" Scale9Width="16" Scale9Height="8" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="138.0000" Y="138.0000" />
                        <Children>
                          <AbstractNodeData Name="Text_rank" ActionTag="1090445777" Tag="995" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="9.0000" RightMargin="9.0000" TopMargin="137.5800" BottomMargin="-44.5800" FontSize="40" LabelText="排行榜" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="120.0000" Y="45.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="69.0000" Y="-22.0800" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="197" G="154" B="125" />
                            <PrePosition X="0.5000" Y="-0.1600" />
                            <PreSize X="0.8696" Y="0.3261" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="113.3333" Y="-678.9998" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_ranking1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_ranking0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_setting" ActionTag="495772159" Tag="5404" IconVisible="False" LeftMargin="271.0001" RightMargin="-409.0001" TopMargin="609.9999" BottomMargin="-747.9999" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="-1" Scale9OriginY="3" Scale9Width="16" Scale9Height="8" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="138.0000" Y="138.0000" />
                        <Children>
                          <AbstractNodeData Name="Text_setting" ActionTag="105537792" Tag="994" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="29.0000" RightMargin="29.0000" TopMargin="137.5800" BottomMargin="-44.5800" FontSize="40" LabelText="设置" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="80.0000" Y="45.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="69.0000" Y="-22.0800" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="197" G="154" B="125" />
                            <PrePosition X="0.5000" Y="-0.1600" />
                            <PreSize X="0.5797" Y="0.3261" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="340.0001" Y="-678.9999" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_set1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_set0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_reset_out" ActionTag="745021524" Tag="1416" IconVisible="False" LeftMargin="401.4226" RightMargin="-521.4226" TopMargin="-648.4785" BottomMargin="528.4785" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="33" RightEage="33" TopEage="30" BottomEage="30" Scale9OriginX="33" Scale9OriginY="30" Scale9Width="54" Scale9Height="60" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="120.0000" Y="120.0000" />
                        <Children>
                          <AbstractNodeData Name="text_out" ActionTag="262590293" VisibleForFrame="False" Tag="1417" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="20.0000" RightMargin="20.0000" TopMargin="37.5000" BottomMargin="37.5000" FontSize="40" LabelText="结束" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="80.0000" Y="45.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="60.0000" Y="60.0000" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="52" G="84" B="129" />
                            <PrePosition X="0.5000" Y="0.5000" />
                            <PreSize X="0.6667" Y="0.3750" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="461.4226" Y="588.4785" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="ui_btn_close3.png" Plist="ui1.plist" />
                        <PressedFileData Type="PlistSubImage" Path="ui_btn_close3.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="ui_btn_close2.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_2_0" ActionTag="-1581628654" Tag="250" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-462.0000" RightMargin="-462.0000" TopMargin="796.9996" BottomMargin="-812.9996" FlipY="True" LeftEage="315" RightEage="315" TopEage="5" BottomEage="5" Scale9OriginX="-269" Scale9OriginY="5" Scale9Width="584" Scale9Height="36" ctype="ImageViewObjectData">
                        <Size X="924.0000" Y="16.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="-804.9996" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="540.0000" Y="720.0000" />
                    <Scale ScaleX="0.6000" ScaleY="0.6000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5000" />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" />
                <Position X="540.0000" Y="0.0002" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.0000" />
                <PreSize X="1.0000" Y="0.6410" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position Y="-140.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition Y="-0.0972" />
            <PreSize X="1.0000" Y="1.5600" />
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