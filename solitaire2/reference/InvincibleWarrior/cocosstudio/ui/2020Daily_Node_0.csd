<GameFile>
  <PropertyGroup Name="2020Daily_Node_0" Type="Node" ID="bb2e00bd-1301-4764-9cd2-4abebc3c3d15" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="85" Speed="1.0000" ActivedAnimationName="start">
        <Timeline ActionTag="-1553922272" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.9000" Y="0.9000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="45" X="1.5000" Y="1.5000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1553922272" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="5" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="20" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="55" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1374067233" Property="Scale">
          <ScaleFrame FrameIndex="30" X="0.9000" Y="0.9000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="1.5000" Y="1.5000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1374067233" Property="Alpha">
          <IntFrame FrameIndex="30" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="35" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="50" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="85" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="loop" StartIndex="0" EndIndex="90">
          <RenderColor A="255" R="255" G="228" B="196" />
        </AnimationInfo>
        <AnimationInfo Name="start" StartIndex="110" EndIndex="145">
          <RenderColor A="255" R="244" G="164" B="96" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="269" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image_root" ActionTag="-683657868" Tag="270" IconVisible="False" LeftMargin="-74.0000" RightMargin="-74.0000" TopMargin="-81.5000" BottomMargin="-81.5000" TouchEnable="True" LeftEage="36" RightEage="36" TopEage="35" BottomEage="35" Scale9OriginX="36" Scale9OriginY="35" Scale9Width="76" Scale9Height="93" ctype="ImageViewObjectData">
            <Size X="148.0000" Y="163.0000" />
            <Children>
              <AbstractNodeData Name="Daily_Daily4_1" Visible="False" ActionTag="-1553922272" VisibleForFrame="False" Alpha="0" Tag="2008" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="29.5000" RightMargin="29.5000" TopMargin="35.3700" BottomMargin="38.6300" ctype="SpriteObjectData">
                <Size X="89.0000" Y="89.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="74.0000" Y="83.1300" />
                <Scale ScaleX="0.9000" ScaleY="0.9000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5100" />
                <PreSize X="0.6014" Y="0.5460" />
                <FileData Type="PlistSubImage" Path="daily/Challenge_lanyuan4.png" Plist="ui1.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Daily_Daily4_1_0" Visible="False" ActionTag="-1374067233" VisibleForFrame="False" Alpha="0" Tag="2010" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="29.5000" RightMargin="29.5000" TopMargin="35.3700" BottomMargin="38.6300" ctype="SpriteObjectData">
                <Size X="89.0000" Y="89.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="74.0000" Y="83.1300" />
                <Scale ScaleX="0.9000" ScaleY="0.9000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5100" />
                <PreSize X="0.6014" Y="0.5460" />
                <FileData Type="PlistSubImage" Path="daily/Challenge_lanyuan4.png" Plist="ui1.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_day_0" Visible="False" ActionTag="909579043" Tag="12" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="51.5000" RightMargin="51.5000" TopMargin="56.6100" BottomMargin="66.3900" LabelText="12" ctype="TextBMFontObjectData">
                <Size X="45.0000" Y="40.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="74.0000" Y="86.3900" />
                <Scale ScaleX="1.3100" ScaleY="1.3100" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5300" />
                <PreSize X="0.3041" Y="0.2454" />
                <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num0.fnt" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_cown" ActionTag="-117737818" Tag="2707" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="74.0000" RightMargin="74.0000" TopMargin="42.3800" BottomMargin="120.6200" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Sprite_cown" ActionTag="-1729961666" Tag="1921" IconVisible="False" LeftMargin="-48.0000" RightMargin="-48.0000" TopMargin="-61.0000" BottomMargin="-31.0000" ctype="SpriteObjectData">
                    <Size X="96.0000" Y="92.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="15.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="daily/Challenge_WG3.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="74.0000" Y="120.6200" />
                <Scale ScaleX="0.9500" ScaleY="0.9500" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.7400" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_67" ActionTag="-1510804378" Tag="13360" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="74.0000" RightMargin="74.0000" TopMargin="81.5000" BottomMargin="81.5000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Text_seven" ActionTag="-1520507475" Tag="13359" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-18.5000" RightMargin="-18.5000" TopMargin="-66.9000" BottomMargin="29.9000" FontSize="37" LabelText="日" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="37.0000" Y="37.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="48.4000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_day" ActionTag="1881511693" Tag="271" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-22.5000" RightMargin="-22.5000" TopMargin="-9.0000" BottomMargin="-31.0000" LabelText="12" ctype="TextBMFontObjectData">
                    <Size X="45.0000" Y="40.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-11.0000" />
                    <Scale ScaleX="1.4000" ScaleY="1.4000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num0.fnt" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="74.0000" Y="81.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="daily/Daily_Daily4.png" Plist="ui1.plist" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>