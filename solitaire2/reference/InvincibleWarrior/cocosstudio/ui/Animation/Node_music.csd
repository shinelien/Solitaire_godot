<GameFile>
  <PropertyGroup Name="Node_music" Type="Node" ID="547d8365-3ab5-487b-b631-a710d66abc9c" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="40" Speed="1.0000" ActivedAnimationName="Start">
        <Timeline ActionTag="1647486142" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="43.0059" Y="80.9482">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1647486142" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.7000" Y="0.7000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.6400" Y="0.6400">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1647486142" Property="Alpha">
          <IntFrame FrameIndex="5" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="40" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="50">
          <RenderColor A="150" R="255" G="215" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="15802" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Ui_music_237" ActionTag="1647486142" Alpha="167" Tag="16094" RotationSkewX="-1.0000" RotationSkewY="-0.9996" IconVisible="False" LeftMargin="-35.2225" RightMargin="-71.7775" TopMargin="-102.4030" BottomMargin="-33.5970" ctype="SpriteObjectData">
            <Size X="107.0000" Y="136.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="18.2775" Y="34.4030" />
            <Scale ScaleX="0.6745" ScaleY="0.6745" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="Ui_music.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>