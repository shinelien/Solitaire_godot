<GameFile>
  <PropertyGroup Name="win_star" Type="Node" ID="03610654-cca9-4dbb-b420-0273478e13b7" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="152" Speed="1.0000" ActivedAnimationName="start1">
        <Timeline ActionTag="-1129582478" Property="Scale">
          <ScaleFrame FrameIndex="0" Tween="False" X="1.0000" Y="1.0000" />
          <ScaleFrame FrameIndex="30" X="0.3700" Y="0.3700">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="70" X="1.3000" Y="1.3000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="105" X="1.4000" Y="1.4000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="151" X="0.5400" Y="0.5400">
            <EasingData Type="4" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1129582478" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" Tween="False" X="0.0000" Y="0.0000" />
          <ScaleFrame FrameIndex="30" X="-180.0000" Y="-180.0000">
            <EasingData Type="20" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="152" X="14.0000" Y="14.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1129582478" Property="Alpha">
          <IntFrame FrameIndex="0" Tween="False" Value="255" />
          <IntFrame FrameIndex="30" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="45" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="145" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="152" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1129582478" Property="Position">
          <PointFrame FrameIndex="0" Tween="False" X="0.0001" Y="0.0000" />
          <PointFrame FrameIndex="30" X="0.0001" Y="0.0000">
            <EasingData Type="8" />
          </PointFrame>
          <PointFrame FrameIndex="105" X="0.0001" Y="-100.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="152" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start0" StartIndex="0" EndIndex="20">
          <RenderColor A="255" R="255" G="160" B="122" />
        </AnimationInfo>
        <AnimationInfo Name="start1" StartIndex="30" EndIndex="152">
          <RenderColor A="255" R="250" G="128" B="114" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="210" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="win_star0_2" ActionTag="-1129582478" Tag="299" RotationSkewX="-8.4759" RotationSkewY="-8.4759" IconVisible="False" LeftMargin="-108.4999" RightMargin="-108.5001" TopMargin="-7.2370" BottomMargin="-206.7630" ctype="SpriteObjectData">
            <Size X="217.0000" Y="214.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="0.0001" Y="-99.7630" />
            <Scale ScaleX="1.3901" ScaleY="1.3901" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="win_star0.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>