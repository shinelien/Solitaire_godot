<GameFile>
  <PropertyGroup Name="man" Type="Node" ID="c6a0cce1-458c-4f6e-a494-d7374e5ef89a" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="40" Speed="1.0000" ActivedAnimationName="idle">
        <Timeline ActionTag="-1730718085" Property="FileData">
          <TextureFrame FrameIndex="10" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/Worker4_1.png" Plist="ui1.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/Worker4_2.png" Plist="ui1.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="20" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/Worker4_3.png" Plist="ui1.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="25" Tween="False">
            <TextureFile Type="PlistSubImage" Path="gif/Worker4_0.png" Plist="ui1.plist" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="-1730718085" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="36" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="-1469361999" Property="VisibleForFrame">
          <BoolFrame FrameIndex="39" Tween="False" Value="False" />
          <BoolFrame FrameIndex="40" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="loop" StartIndex="0" EndIndex="35">
          <RenderColor A="255" R="255" G="240" B="245" />
        </AnimationInfo>
        <AnimationInfo Name="idle" StartIndex="40" EndIndex="40">
          <RenderColor A="255" R="153" G="50" B="204" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="287" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Sprite_1" ActionTag="-1730718085" VisibleForFrame="False" Tag="288" IconVisible="False" LeftMargin="-34.5000" RightMargin="-34.5000" TopMargin="-58.5000" BottomMargin="-46.5000" ctype="SpriteObjectData">
            <Size X="69.0000" Y="105.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="6.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="gif/Worker4_0.png" Plist="ui1.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sprite_reward" ActionTag="-1469361999" Tag="684" IconVisible="False" LeftMargin="-33.0000" RightMargin="-33.0000" TopMargin="-33.0000" BottomMargin="-33.0000" ctype="SpriteObjectData">
            <Size X="66.0000" Y="66.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.4000" ScaleY="1.4000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="senceicon/icon_fish1_0.png" Plist="ui1.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>