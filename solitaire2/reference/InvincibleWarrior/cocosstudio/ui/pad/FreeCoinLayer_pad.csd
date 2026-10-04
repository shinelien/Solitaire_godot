<GameFile>
  <PropertyGroup Name="FreeCoinLayer_pad" Type="Layer" ID="23c811ae-4196-4dcc-99d5-22647b7d46bc" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="70" Speed="1.0000" ActivedAnimationName="loop">
        <Timeline ActionTag="657461624" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="26" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="615318219" Property="VisibleForFrame">
          <BoolFrame FrameIndex="34" Tween="False" Value="False" />
          <BoolFrame FrameIndex="35" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-536420208" Property="Scale">
          <ScaleFrame FrameIndex="55" X="0.5000" Y="0.5000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="70" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-536420208" Property="Alpha">
          <IntFrame FrameIndex="55" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="70" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="1227162263" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.5300" Y="0.5300">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="26" X="0.7000" Y="0.7000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1227162263" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="26" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="loop" StartIndex="0" EndIndex="90">
          <RenderColor A="255" R="220" G="220" B="220" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="151" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Text_10" ActionTag="-208486314" Tag="40507" IconVisible="False" LeftMargin="1842.4158" RightMargin="-906.4158" TopMargin="2415.5715" BottomMargin="-993.5715" FontSize="18" LabelText="需要观看一段视频" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="144.0000" Y="18.0000" />
            <AnchorPoint ScaleX="0.5529" ScaleY="0.6818" />
            <Position X="1922.0333" Y="-981.2991" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="70" G="234" B="70" />
            <PrePosition X="1.7797" Y="-0.6815" />
            <PreSize X="0.1333" Y="0.0125" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_close" ActionTag="657461624" Alpha="0" Tag="40506" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="0.0012" RightMargin="-0.0012" TopMargin="-510.0000" BottomMargin="-300.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="2250.0000" />
            <AnchorPoint />
            <Position X="0.0012" Y="-300.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0000" Y="-0.2083" />
            <PreSize X="1.0000" Y="1.5625" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_freecoin" ActionTag="1716417562" Tag="40470" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <Children>
              <AbstractNodeData Name="Node_3" ActionTag="1227162263" Alpha="0" Tag="40471" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="662.4000" BottomMargin="777.6000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_1" ActionTag="1297689395" Tag="40472" IconVisible="False" LeftMargin="-405.0000" RightMargin="-405.0000" TopMargin="-600.0000" BottomMargin="-600.0000" Scale9Enable="True" LeftEage="89" RightEage="93" TopEage="105" BottomEage="109" Scale9OriginX="89" Scale9OriginY="105" Scale9Width="205" Scale9Height="262" ctype="ImageViewObjectData">
                    <Size X="810.0000" Y="1200.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="244" B="229" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="fish_ui/fish_ui_bg0.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_1" ActionTag="31876002" Tag="40473" IconVisible="True" PositionPercentXEnabled="True" TopMargin="-357.0000" BottomMargin="357.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Text_title" ActionTag="-1444054846" Tag="40474" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-100.0000" RightMargin="-100.0000" TopMargin="-177.6188" BottomMargin="127.6188" FontSize="50" LabelText="领取金币" ShadowOffsetX="0.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="200.0000" Y="50.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="152.6188" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="97" G="47" B="0" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="357.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_2" ActionTag="1069666914" Tag="40475" IconVisible="True" PositionPercentXEnabled="True" TopMargin="-225.1152" BottomMargin="225.1152" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Particle_1_0" ActionTag="615318219" VisibleForFrame="False" Tag="40476" IconVisible="True" PositionPercentXEnabled="True" TopMargin="-38.5856" BottomMargin="38.5856" ctype="ParticleObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position Y="38.5856" />
                        <Scale ScaleX="2.3792" ScaleY="1.7704" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="Particicle/Start_BG.plist" Plist="" />
                        <BlendFunc Src="1" Dst="1" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="ui_gift3_4_1" ActionTag="1125101879" Tag="40477" IconVisible="False" LeftMargin="-278.7280" RightMargin="68.7280" TopMargin="-56.9568" BottomMargin="-43.0432" ctype="SpriteObjectData">
                        <Size X="210.0000" Y="100.0000" />
                        <AnchorPoint ScaleX="0.4923" />
                        <Position X="-175.3450" Y="-43.0432" />
                        <Scale ScaleX="0.8200" ScaleY="0.8200" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="ui_gift3.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="ui_gift4_5" ActionTag="2006217670" Tag="40478" IconVisible="False" LeftMargin="-193.6982" RightMargin="-219.3018" TopMargin="-88.7774" BottomMargin="-78.2226" ctype="SpriteObjectData">
                        <Size X="413.0000" Y="167.0000" />
                        <AnchorPoint ScaleX="0.5000" />
                        <Position X="12.8018" Y="-78.2226" />
                        <Scale ScaleX="1.4500" ScaleY="1.4500" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="ui_gift4.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="ui_gift3_4_0" ActionTag="-993536145" Tag="40479" IconVisible="False" LeftMargin="-8.6417" RightMargin="-201.3583" TopMargin="-16.1400" BottomMargin="-83.8600" FlipX="True" ctype="SpriteObjectData">
                        <Size X="210.0000" Y="100.0000" />
                        <AnchorPoint ScaleX="0.4923" />
                        <Position X="94.7413" Y="-83.8600" />
                        <Scale ScaleX="0.9700" ScaleY="0.9700" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="ui_gift3.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="ui_gift3_4" ActionTag="-707120538" Tag="40480" IconVisible="False" LeftMargin="-104.9043" RightMargin="-105.0957" TopMargin="-5.6426" BottomMargin="-94.3574" ctype="SpriteObjectData">
                        <Size X="210.0000" Y="100.0000" />
                        <AnchorPoint ScaleX="0.4923" />
                        <Position X="-1.5213" Y="-94.3574" />
                        <Scale ScaleX="1.0900" ScaleY="1.0900" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="ui_gift3.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="225.1152" />
                    <Scale ScaleX="1.1000" ScaleY="1.1000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_close" ActionTag="1035145255" Tag="40481" IconVisible="False" LeftMargin="333.5005" RightMargin="-437.5005" TopMargin="-610.5636" BottomMargin="480.5636" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="74" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="104.0000" Y="130.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="385.5005" Y="545.5636" />
                    <Scale ScaleX="1.3000" ScaleY="1.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="fish_ui/fish_btn_close0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_lingqu" Visible="False" ActionTag="-536420208" VisibleForFrame="False" Alpha="0" Tag="40482" IconVisible="False" LeftMargin="-1173.3425" RightMargin="573.3425" TopMargin="353.7789" BottomMargin="-493.7789" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="40" RightEage="40" TopEage="11" BottomEage="11" Scale9OriginX="40" Scale9OriginY="11" Scale9Width="191" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="600.0000" Y="140.0000" />
                    <Children>
                      <AbstractNodeData Name="text_lingqu" ActionTag="1839380428" Tag="40483" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="255.0000" RightMargin="255.0000" TopMargin="44.7000" BottomMargin="50.3000" FontSize="45" LabelText="领取" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="90.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="300.0000" Y="72.8000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5200" />
                        <PreSize X="0.1500" Y="0.3214" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn1_btn0_1_1" ActionTag="-152855370" Alpha="127" Tag="40484" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="600.0000" RightMargin="-40.0000" TopMargin="47.2000" BottomMargin="52.8000" ctype="SpriteObjectData">
                        <Size X="40.0000" Y="40.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="600.0000" Y="72.8000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="139" G="105" B="20" />
                        <PrePosition X="1.0000" Y="0.5200" />
                        <PreSize X="0.0667" Y="0.2857" />
                        <FileData Type="PlistSubImage" Path="btn_btn0.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn1_btn0_1_0_0" ActionTag="-13798560" Alpha="127" Tag="40485" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-40.0000" RightMargin="600.0000" TopMargin="47.2000" BottomMargin="52.8000" FlipX="True" ctype="SpriteObjectData">
                        <Size X="40.0000" Y="40.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position Y="72.8000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="139" G="105" B="20" />
                        <PrePosition Y="0.5200" />
                        <PreSize X="0.0667" Y="0.2857" />
                        <FileData Type="PlistSubImage" Path="btn_btn0.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-873.3425" Y="-423.7789" />
                    <Scale ScaleX="0.5000" ScaleY="0.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_blue0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_guankan" ActionTag="1845752305" Tag="40486" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-300.0000" RightMargin="-300.0000" TopMargin="72.0090" BottomMargin="-253.0090" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="40" RightEage="40" TopEage="32" BottomEage="32" Scale9OriginX="40" Scale9OriginY="32" Scale9Width="191" Scale9Height="58" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="600.0000" Y="181.0000" />
                    <Children>
                      <AbstractNodeData Name="Particle_1" ActionTag="1845990599" Tag="40487" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="300.0000" RightMargin="300.0000" TopMargin="43.4400" BottomMargin="137.5600" ctype="ParticleObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position X="300.0000" Y="137.5600" />
                        <Scale ScaleX="1.4000" ScaleY="1.4000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.7600" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="Particicle/btn.plist" Plist="" />
                        <BlendFunc Src="770" Dst="1" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="FileNode_1" ActionTag="1195979140" Tag="40488" RotationSkewY="0.0023" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="173.1000" RightMargin="426.9000" TopMargin="84.1469" BottomMargin="96.8531" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <AnchorPoint />
                        <Position X="173.1000" Y="96.8531" />
                        <Scale ScaleX="1.2000" ScaleY="1.2000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.2885" Y="0.5351" />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="Normal" Path="ui/Animation/Node_currency.csd" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_12" Visible="False" ActionTag="-1841963663" VisibleForFrame="False" Tag="40498" IconVisible="False" LeftMargin="507.7379" RightMargin="42.2621" TopMargin="70.7100" BottomMargin="60.2900" FontSize="50" LabelText="x2" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ShadowEnabled="True" ctype="TextObjectData">
                        <Size X="50.0000" Y="50.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="532.7379" Y="85.2900" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.8879" Y="0.4712" />
                        <PreSize X="0.0833" Y="0.2762" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="67" G="148" B="255" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="ui_AD_0_20" ActionTag="-205005541" Alpha="133" Tag="40499" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="11.3200" RightMargin="476.6800" TopMargin="27.9478" BottomMargin="41.0522" ctype="SpriteObjectData">
                        <Size X="112.0000" Y="112.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="67.3200" Y="97.0522" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="166" />
                        <PrePosition X="0.1122" Y="0.5362" />
                        <PreSize X="0.1867" Y="0.6188" />
                        <FileData Type="PlistSubImage" Path="btn1_ad0.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_guankan" Visible="False" ActionTag="1766364891" VisibleForFrame="False" Tag="40500" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="198.0000" RightMargin="222.0000" TopMargin="64.3800" BottomMargin="71.6200" FontSize="45" LabelText="打开宝箱" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="180.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="288.0000" Y="94.1200" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.4800" Y="0.5200" />
                        <PreSize X="0.3000" Y="0.2486" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="BitmapFontLabel_goldNum" ActionTag="1934257901" Tag="40501" IconVisible="False" LeftMargin="241.8665" RightMargin="152.1335" TopMargin="38.7755" BottomMargin="52.2245" LabelText="+100" ctype="TextBMFontObjectData">
                        <Size X="206.0000" Y="90.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="344.8665" Y="97.2245" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5748" Y="0.5372" />
                        <PreSize X="0.3433" Y="0.4972" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-162.5090" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="255" G="255" B="255" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_yellow1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_yellow0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_miaoshu" ActionTag="-390706665" Tag="40502" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-187.5000" RightMargin="-187.5000" TopMargin="-76.1115" BottomMargin="26.1115" FontSize="50" LabelText="你将获得200金币" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="375.0000" Y="50.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="51.1115" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg4_1_0_0_0" ActionTag="1256105709" Tag="40503" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-283.0000" RightMargin="-283.0000" TopMargin="-472.3963" BottomMargin="432.3963" ctype="SpriteObjectData">
                    <Size X="566.0000" Y="40.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="452.3963" />
                    <Scale ScaleX="0.9000" ScaleY="0.9000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg4.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_game" ActionTag="-1392642977" Tag="40504" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-300.0000" RightMargin="-300.0000" TopMargin="298.4403" BottomMargin="-479.4403" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="40" RightEage="40" TopEage="11" BottomEage="11" Scale9OriginX="40" Scale9OriginY="11" Scale9Width="191" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="600.0000" Y="181.0000" />
                    <Children>
                      <AbstractNodeData Name="text_game" ActionTag="-258186047" Tag="40505" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="200.0000" RightMargin="200.0000" TopMargin="46.8800" BottomMargin="54.1200" FontSize="80" LabelText="Store" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="200.0000" Y="80.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="300.0000" Y="94.1200" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5200" />
                        <PreSize X="0.3333" Y="0.4420" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-388.9403" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_blue0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="777.6000" />
                <Scale ScaleX="0.5300" ScaleY="0.5300" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5400" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="720.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_1000" Visible="False" ActionTag="-564359241" VisibleForFrame="False" Tag="40469" IconVisible="False" LeftMargin="42.5573" RightMargin="837.4427" TopMargin="-187.6671" BottomMargin="1484.5814" TouchEnable="True" FontSize="50" ButtonText="+1000" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="200.0000" Y="143.0856" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="142.5573" Y="1556.1243" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1320" Y="1.0806" />
            <PreSize X="0.1852" Y="0.0994" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>