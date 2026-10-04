<GameFile>
  <PropertyGroup Name="2020menu1" Type="Node" ID="bb391955-fba1-4b4b-9e85-14e2bc03efc5" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="51" Speed="1.0000" ActivedAnimationName="Start1">
        <Timeline ActionTag="493062296" Property="Position">
          <PointFrame FrameIndex="0" X="-14.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="15" Tween="False" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="36" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="51" X="-14.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="493062296" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" Tween="False" X="-317.0000" Y="-317.0000" />
          <ScaleFrame FrameIndex="26" X="-317.0000" Y="-317.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="51" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1606805613" Property="Position">
          <PointFrame FrameIndex="0" X="14.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" Tween="False" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="26" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="51" X="14.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1606805613" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" Tween="False" X="-227.0000" Y="-227.0000" />
          <ScaleFrame FrameIndex="26" X="-227.0000" Y="-227.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="51" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start0" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="128" G="0" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="Start1" StartIndex="26" EndIndex="51">
          <RenderColor A="255" R="255" G="228" B="225" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="1428" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="game_new2_1" ActionTag="493062296" Tag="1429" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-35.5000" RightMargin="-7.5000" TopMargin="-41.0000" BottomMargin="-41.0000" ctype="SpriteObjectData">
            <Size X="43.0000" Y="82.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-14.0000" />
            <Scale ScaleX="1.2000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="game_new2.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="game_new2_1_0" ActionTag="1606805613" Tag="1430" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="-7.5000" RightMargin="-35.5000" TopMargin="-41.0000" BottomMargin="-41.0000" ctype="SpriteObjectData">
            <Size X="43.0000" Y="82.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="14.0000" />
            <Scale ScaleX="1.2000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="game_new2.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>