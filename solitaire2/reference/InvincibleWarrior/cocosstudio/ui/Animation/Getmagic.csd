<GameFile>
  <PropertyGroup Name="Getmagic" Type="Node" ID="f4853c3c-84b2-446e-adb9-23804072b9c9" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="135" Speed="1.0000" ActivedAnimationName="Start0">
        <Timeline ActionTag="-1458557807" Property="VisibleForFrame">
          <BoolFrame FrameIndex="5" Tween="False" Value="False" />
          <BoolFrame FrameIndex="11" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="115957007" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="278.9420">
            <EasingData Type="1" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="320.9400">
            <EasingData Type="26" />
          </PointFrame>
          <PointFrame FrameIndex="72" X="0.0000" Y="320.9400">
            <EasingData Type="26" />
          </PointFrame>
          <PointFrame FrameIndex="135" X="-4.5234" Y="17.8187">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="115957007" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.5000" Y="0.5000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.8000" Y="0.8000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="72" X="0.8000" Y="0.8000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="110" X="0.5000" Y="0.5000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="115957007" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="15" Tween="False" Value="255" />
          <IntFrame FrameIndex="72" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="90" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start0" StartIndex="0" EndIndex="135">
          <RenderColor A="255" R="255" G="69" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="1231" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Navigate17_1" ActionTag="115957007" Alpha="0" Tag="1232" RotationSkewX="50.0020" RotationSkewY="50.0005" IconVisible="False" LeftMargin="-51.3036" RightMargin="-41.6964" TopMargin="-114.2418" BottomMargin="-65.7582" ctype="SpriteObjectData">
            <Size X="93.0000" Y="180.0000" />
            <Children>
              <AbstractNodeData Name="Particle_6" ActionTag="-1458557807" Tag="1581" IconVisible="True" LeftMargin="43.2416" RightMargin="49.7584" TopMargin="66.4367" BottomMargin="113.5633" ctype="ParticleObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="43.2416" Y="113.5633" />
                <Scale ScaleX="2.0000" ScaleY="2.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4650" Y="0.6309" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Particicle/Magic0.plist" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.3600" />
            <Position X="-4.8036" Y="-0.9582" />
            <Scale ScaleX="0.5484" ScaleY="0.5484" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="Magic_0.png" Plist="ui.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>