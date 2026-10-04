<GameFile>
  <PropertyGroup Name="Score" Type="Node" ID="9e7eaa75-adaf-4ccf-b5ad-547a5f9e1e5c" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="120" Speed="1.0000" ActivedAnimationName="start0">
        <Timeline ActionTag="1137670573" Property="Position">
          <PointFrame FrameIndex="0" X="24.0000" Y="70.0000">
            <EasingData Type="20" />
          </PointFrame>
          <PointFrame FrameIndex="35" X="24.0000" Y="170.0000">
            <EasingData Type="8" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1137670573" Property="Alpha">
          <IntFrame FrameIndex="25" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="60" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="1137670573" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.8000" Y="0.8000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="35" X="0.7000" Y="0.7000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="159174186" Property="Position">
          <PointFrame FrameIndex="60" X="20.0000" Y="70.0000">
            <EasingData Type="8" />
          </PointFrame>
          <PointFrame FrameIndex="95" X="20.0000" Y="150.0000">
            <EasingData Type="8" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="159174186" Property="Alpha">
          <IntFrame FrameIndex="85" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="120" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="159174186" Property="VisibleForFrame">
          <BoolFrame FrameIndex="60" Tween="False" Value="False" />
          <BoolFrame FrameIndex="61" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start0" StartIndex="0" EndIndex="60">
          <RenderColor A="255" R="188" G="143" B="143" />
        </AnimationInfo>
        <AnimationInfo Name="start1" StartIndex="60" EndIndex="120">
          <RenderColor A="255" R="176" G="196" B="222" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="665" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Node_Addpoints" ActionTag="1137670573" Alpha="233" Tag="667" IconVisible="True" LeftMargin="24.0000" RightMargin="-24.0000" TopMargin="-167.9796" BottomMargin="167.9796" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Text_add" ActionTag="-1048380709" Tag="666" IconVisible="False" LeftMargin="-33.5000" RightMargin="-33.5000" TopMargin="-45.0000" BottomMargin="-45.0000" LabelText="5" ctype="TextBMFontObjectData">
                <Size X="67.0000" Y="90.0000" />
                <Children>
                  <AbstractNodeData Name="BitmapFontLabel_1" ActionTag="716669894" Tag="51" IconVisible="False" LeftMargin="-67.0000" RightMargin="62.0000" TopMargin="-2.0000" BottomMargin="2.0000" LabelText="+" ctype="TextBMFontObjectData">
                    <Size X="72.0000" Y="90.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-31.0000" Y="47.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="-0.4627" Y="0.5222" />
                    <PreSize X="1.0746" Y="1.0000" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/level_gre2x.fnt" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <LabelBMFontFile_CNB Type="Normal" Path="font/level_gre2x.fnt" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="24.0000" Y="167.9796" />
            <Scale ScaleX="0.7200" ScaleY="0.7200" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Node_Minuspoints" ActionTag="159174186" VisibleForFrame="False" Tag="668" IconVisible="True" LeftMargin="20.0000" RightMargin="-20.0000" TopMargin="-70.0000" BottomMargin="70.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Text_minus" ActionTag="750174317" Tag="669" IconVisible="False" LeftMargin="-33.5000" RightMargin="-33.5000" TopMargin="-45.0000" BottomMargin="-45.0000" LabelText="5" ctype="TextBMFontObjectData">
                <Size X="67.0000" Y="90.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <LabelBMFontFile_CNB Type="Normal" Path="font/level_red2x.fnt" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="20.0000" Y="70.0000" />
            <Scale ScaleX="0.8000" ScaleY="0.8000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>