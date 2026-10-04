<GameFile>
  <PropertyGroup Name="nomove_pad" Type="Layer" ID="d0e1a5e2-8058-47ad-9e28-5dac676d7695" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="35" Speed="1.0000" ActivedAnimationName="Start0">
        <Timeline ActionTag="1785220110" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-662901783" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.7000" Y="0.0010">
            <EasingData Type="21" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="35" X="0.7000" Y="0.7000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-662901783" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="3" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start0" StartIndex="0" EndIndex="125">
          <RenderColor A="255" R="0" G="255" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="270" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Panel_close" ActionTag="1689201027" Tag="3158" IconVisible="False" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_4" ActionTag="-662901783" Tag="649" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-235.0000" RightMargin="-235.0000" TopMargin="578.5399" BottomMargin="578.5399" TouchEnable="True" ClipAble="False" BackColorAlpha="153" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1550.0000" Y="282.9201" />
            <Children>
              <AbstractNodeData Name="btn_use" ActionTag="-1842803808" Tag="681" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="833.0001" RightMargin="337.0000" TopMargin="133.7025" BottomMargin="9.2176" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="40" RightEage="40" TopEage="11" BottomEage="11" Scale9OriginX="40" Scale9OriginY="11" Scale9Width="191" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="380.0000" Y="140.0000" />
                <Children>
                  <AbstractNodeData Name="Particle_1" ActionTag="1755164329" Tag="682" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="190.0000" RightMargin="190.0000" TopMargin="33.6000" BottomMargin="106.4000" ctype="ParticleObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="190.0000" Y="106.4000" />
                    <Scale ScaleX="1.4000" ScaleY="1.4000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.7600" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Particicle/btn.plist" Plist="" />
                    <BlendFunc Src="770" Dst="1" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn1_btn0_1" ActionTag="666386830" Alpha="127" Tag="687" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="380.0000" RightMargin="-25.0000" TopMargin="48.2000" BottomMargin="53.8000" ctype="SpriteObjectData">
                    <Size X="25.0000" Y="38.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="380.0000" Y="72.8000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="139" G="105" B="20" />
                    <PrePosition X="1.0000" Y="0.5200" />
                    <PreSize X="0.0658" Y="0.2714" />
                    <FileData Type="PlistSubImage" Path="btn_btn0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn1_btn0_1_0" ActionTag="-1049696055" Alpha="127" Tag="688" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-25.0000" RightMargin="380.0000" TopMargin="48.2000" BottomMargin="53.8000" FlipX="True" ctype="SpriteObjectData">
                    <Size X="25.0000" Y="38.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position Y="72.8000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="139" G="105" B="20" />
                    <PrePosition Y="0.5200" />
                    <PreSize X="0.0658" Y="0.2714" />
                    <FileData Type="PlistSubImage" Path="btn_btn0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_guankan" ActionTag="-1318447851" Tag="689" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="151.7000" RightMargin="121.3000" TopMargin="31.8000" BottomMargin="40.2000" FontSize="60" LabelText="Use" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="107.0000" Y="68.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="205.2000" Y="74.2000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5400" Y="0.5300" />
                    <PreSize X="0.2816" Y="0.4857" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Particle_1_0_0" ActionTag="1785220110" Tag="670" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="98.8000" RightMargin="281.2000" TopMargin="21.0000" BottomMargin="119.0000" ctype="ParticleObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <Children>
                      <AbstractNodeData Name="Navigate17_1_0" ActionTag="1738277685" Tag="668" RotationSkewX="50.0002" RotationSkewY="49.9994" IconVisible="False" LeftMargin="-127.1007" RightMargin="34.1007" TopMargin="-96.6220" BottomMargin="-83.3780" ctype="SpriteObjectData">
                        <Size X="93.0000" Y="180.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.1367" />
                        <Position X="-80.6007" Y="-58.7720" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.0000" Y="0.0000" />
                        <FileData Type="PlistSubImage" Path="Magic_0.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="98.8000" Y="119.0000" />
                    <Scale ScaleX="1.0933" ScaleY="1.1749" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2600" Y="0.8500" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Particicle/Start_BG.plist" Plist="" />
                    <BlendFunc Src="1" Dst="1" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1023.0001" Y="79.2176" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6600" Y="0.2800" />
                <PreSize X="0.2452" Y="0.4948" />
                <TextColor A="255" R="255" G="255" B="255" />
                <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
                <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn_agian" ActionTag="-1080792577" Tag="671" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="337.0000" RightMargin="833.0000" TopMargin="133.7025" BottomMargin="9.2176" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="40" RightEage="40" TopEage="11" BottomEage="11" Scale9OriginX="40" Scale9OriginY="11" Scale9Width="191" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="380.0000" Y="140.0000" />
                <Children>
                  <AbstractNodeData Name="Particle_1" ActionTag="1648359948" Tag="672" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="190.0000" RightMargin="190.0000" TopMargin="33.6000" BottomMargin="106.4000" ctype="ParticleObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="190.0000" Y="106.4000" />
                    <Scale ScaleX="1.4000" ScaleY="1.4000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.7600" />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Particicle/btn.plist" Plist="" />
                    <BlendFunc Src="770" Dst="1" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn1_btn0_1" ActionTag="1131792168" Alpha="127" Tag="673" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="380.0000" RightMargin="-25.0000" TopMargin="48.2000" BottomMargin="53.8000" ctype="SpriteObjectData">
                    <Size X="25.0000" Y="38.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="380.0000" Y="72.8000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="139" G="105" B="20" />
                    <PrePosition X="1.0000" Y="0.5200" />
                    <PreSize X="0.0658" Y="0.2714" />
                    <FileData Type="PlistSubImage" Path="btn_btn0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn1_btn0_1_0" ActionTag="-1230262803" Alpha="127" Tag="674" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-25.0000" RightMargin="380.0000" TopMargin="48.2000" BottomMargin="53.8000" FlipX="True" ctype="SpriteObjectData">
                    <Size X="25.0000" Y="38.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position Y="72.8000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="139" G="105" B="20" />
                    <PrePosition Y="0.5200" />
                    <PreSize X="0.0658" Y="0.2714" />
                    <FileData Type="PlistSubImage" Path="btn_btn0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_guankan_0" ActionTag="-502519506" Tag="680" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="119.5000" RightMargin="119.5000" TopMargin="34.3000" BottomMargin="42.7000" FontSize="55" LabelText="Agian" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="141.0000" Y="63.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="190.0000" Y="74.2000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5300" />
                    <PreSize X="0.3711" Y="0.4500" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="527.0000" Y="79.2176" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3400" Y="0.2800" />
                <PreSize X="0.2452" Y="0.4948" />
                <TextColor A="255" R="255" G="255" B="255" />
                <PressedFileData Type="PlistSubImage" Path="btn_blue1.png" Plist="ui1.plist" />
                <NormalFileData Type="PlistSubImage" Path="btn_blue0.png" Plist="ui1.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_title" ActionTag="-614592453" Tag="1254" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="546.0000" RightMargin="546.0000" TopMargin="13.9380" BottomMargin="211.9821" FontSize="50" LabelText="ARE YOU STUCK？" ShadowOffsetX="0.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="458.0000" Y="57.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="775.0000" Y="240.4821" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.8500" />
                <PreSize X="0.2955" Y="0.2015" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="97" G="47" B="0" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="540.0000" Y="720.0000" />
            <Scale ScaleX="0.7000" ScaleY="0.7000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.4352" Y="0.1965" />
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