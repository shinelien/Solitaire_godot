<GameFile>
  <PropertyGroup Name="move" Type="Node" ID="fd2d7879-a736-409e-9fb6-30bb4ff1723d" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="55" Speed="1.0000" ActivedAnimationName="start0">
        <Timeline ActionTag="-234581441" Property="Position">
          <PointFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="14" />
          </PointFrame>
          <PointFrame FrameIndex="19" X="20.9085" Y="-51.4719">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-234581441" Property="Scale">
          <ScaleFrame FrameIndex="1" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="19" X="0.9500" Y="0.9500">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-234581441" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="1" Value="51">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="50" Value="51">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="51" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="1439423805" Property="Scale">
          <ScaleFrame FrameIndex="1" X="1.0000" Y="1.0000">
            <EasingData Type="14" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="19" X="1.4000" Y="1.4000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="0.4000" Y="0.4000">
            <EasingData Type="11" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1439423805" Property="Alpha">
          <IntFrame FrameIndex="45" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="55" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start0" StartIndex="0" EndIndex="56">
          <RenderColor A="255" R="250" G="240" B="230" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Node_1_0" ActionTag="1439423805" Tag="5" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="card_0_1_0_2" ActionTag="-234581441" Alpha="0" Tag="6" IconVisible="False" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                <Size X="46.0000" Y="46.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="card_0_1_0_1" ActionTag="-919157334" Tag="7" IconVisible="False" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                <Size X="148.0000" Y="220.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="Level_card1.png" Plist="ui1.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>