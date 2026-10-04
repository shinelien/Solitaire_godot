<GameFile>
  <PropertyGroup Name="Button_Complete" Type="Node" ID="194e8598-cb0e-48b7-8494-6c4347428f12" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="25" Speed="1.0000" ActivedAnimationName="Start">
        <Timeline ActionTag="1381793942" Property="FileData">
          <TextureFrame FrameIndex="1" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/gif_btn0.png" Plist="ui.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="2" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/gif_btn1.png" Plist="ui.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="7" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/gif_btn2.png" Plist="ui.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="10" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/gif_btn3.png" Plist="ui.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="13" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/gif_btn4.png" Plist="ui.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="16" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/gif_btn5.png" Plist="ui.plist" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="1381793942" Property="Alpha">
          <IntFrame FrameIndex="2" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="8" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="11" Value="127">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="18" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="1092217225" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.7000" Y="0.7000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="6" X="1.0391" Y="1.0391">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.9439" Y="0.9439">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="34" G="139" B="34" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="11597" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Button_auto" ActionTag="1092217225" Tag="11599" IconVisible="False" LeftMargin="-260.0001" RightMargin="-259.9999" TopMargin="-103.0002" BottomMargin="-102.9998" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="100" RightEage="100" Scale9OriginX="100" Scale9Width="71" Scale9Height="122" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="520.0000" Y="206.0000" />
            <Children>
              <AbstractNodeData Name="Text_autoComplete" ActionTag="1244309549" Tag="11600" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="32.5000" RightMargin="32.5000" TopMargin="59.7600" BottomMargin="76.2400" FontSize="70" LabelText="Auto Complete" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="455.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="260.0000" Y="111.2400" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5400" />
                <PreSize X="0.8750" Y="0.3398" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Particle_1" ActionTag="-2082689654" Tag="3866" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="260.0000" RightMargin="260.0000" TopMargin="41.1999" BottomMargin="164.8001" ctype="ParticleObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="260.0000" Y="164.8001" />
                <Scale ScaleX="1.4000" ScaleY="1.4000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.8000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Particicle/btn.plist" Plist="" />
                <BlendFunc Src="770" Dst="1" />
              </AbstractNodeData>
              <AbstractNodeData Name="Sprite_1" ActionTag="1381793942" Alpha="0" Tag="3696" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="55.5000" RightMargin="55.5000" TopMargin="53.8800" BottomMargin="62.1200" ctype="SpriteObjectData">
                <Size X="409.0000" Y="90.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="260.0000" Y="107.1200" />
                <Scale ScaleX="1.2266" ScaleY="2.0080" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5200" />
                <PreSize X="0.7865" Y="0.4369" />
                <FileData Type="PlistSubImage" Path="gif/gif_btn0.png" Plist="ui.plist" />
                <BlendFunc Src="1" Dst="1" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-0.0001" Y="0.0002" />
            <Scale ScaleX="0.7000" ScaleY="0.7000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="PlistSubImage" Path="btn_gre2.png" Plist="ui1.plist" />
            <PressedFileData Type="PlistSubImage" Path="btn_gre1.png" Plist="ui1.plist" />
            <NormalFileData Type="PlistSubImage" Path="btn_gre0.png" Plist="ui1.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>