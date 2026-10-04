<GameFile>
  <PropertyGroup Name="Node_DuiHua" Type="Node" ID="f9b08683-22c3-4b27-8920-780c7957d12e" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="450" Speed="1.0000" ActivedAnimationName="start0">
        <Timeline ActionTag="835966727" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0100">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.4000" Y="1.4000">
            <EasingData Type="27" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="835966727" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="150" Tween="False" Value="False" />
          <BoolFrame FrameIndex="300" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="249772545" Property="Scale">
          <ScaleFrame FrameIndex="301" X="0.0100" Y="0.0100">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="320" X="1.4000" Y="1.4000">
            <EasingData Type="27" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="249772545" Property="VisibleForFrame">
          <BoolFrame FrameIndex="301" Tween="False" Value="True" />
          <BoolFrame FrameIndex="450" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start0" StartIndex="0" EndIndex="150">
          <RenderColor A="255" R="153" G="50" B="204" />
        </AnimationInfo>
        <AnimationInfo Name="start1" StartIndex="300" EndIndex="450">
          <RenderColor A="255" R="147" G="112" B="219" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="3815" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image_1" ActionTag="835966727" Tag="20" IconVisible="False" LeftMargin="-60.8971" RightMargin="-9.1029" TopMargin="-42.0100" BottomMargin="-41.9900" Scale9Enable="True" LeftEage="51" RightEage="36" TopEage="27" BottomEage="27" Scale9OriginX="51" Scale9OriginY="27" Scale9Width="24" Scale9Height="30" ctype="ImageViewObjectData">
            <Size X="70.0000" Y="84.0000" />
            <Children>
              <AbstractNodeData Name="Text_duihua" ActionTag="-1596730363" Tag="3816" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="65.0000" RightMargin="-139.0000" TopMargin="11.0400" BottomMargin="36.9600" FontSize="36" LabelText="fullness" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="144.0000" Y="36.0000" />
                <AnchorPoint />
                <Position X="65.0000" Y="36.9600" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="8" B="35" />
                <PrePosition X="0.9286" Y="0.4400" />
                <PreSize X="2.0571" Y="0.4286" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Sprite_DuiHua" ActionTag="1945478454" Tag="21" IconVisible="False" LeftMargin="9.7800" RightMargin="11.2200" TopMargin="6.5400" BottomMargin="24.4600" ctype="SpriteObjectData">
                <Size X="49.0000" Y="53.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="34.2800" Y="50.9600" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4897" Y="0.6067" />
                <PreSize X="0.7000" Y="0.6310" />
                <FileData Type="PlistSubImage" Path="emoji/ele.png" Plist="ui.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="-60.8971" Y="-41.9900" />
            <Scale ScaleX="0.0100" ScaleY="0.0100" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="fish_duihua.png" Plist="ui.plist" />
          </AbstractNodeData>
          <AbstractNodeData Name="Image_1_0" ActionTag="249772545" Tag="22" IconVisible="False" LeftMargin="-37.5000" RightMargin="-37.5000" TopMargin="-42.0100" BottomMargin="-41.9900" Scale9Enable="True" LeftEage="51" RightEage="36" TopEage="27" BottomEage="27" Scale9OriginX="51" Scale9OriginY="27" Scale9Width="24" Scale9Height="30" ctype="ImageViewObjectData">
            <Size X="75.0000" Y="84.0000" />
            <Children>
              <AbstractNodeData Name="Sprite_emoji" ActionTag="1077302810" Tag="24" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="13.0000" RightMargin="13.0000" TopMargin="6.5373" BottomMargin="24.4627" ctype="SpriteObjectData">
                <Size X="49.0000" Y="53.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="37.5000" Y="50.9627" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.6067" />
                <PreSize X="0.6533" Y="0.6310" />
                <FileData Type="PlistSubImage" Path="emoji/ele.png" Plist="ui.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" />
            <Position Y="-41.9900" />
            <Scale ScaleX="0.0100" ScaleY="0.0100" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="fish_duihua.png" Plist="ui.plist" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>