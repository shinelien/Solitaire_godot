<GameFile>
  <PropertyGroup Name="2020HomeView_Mission" Type="Layer" ID="5ca74604-1449-4604-b5c8-1b376af32465" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="70" Speed="1.0000" ActivedAnimationName="In">
        <Timeline ActionTag="2015859816" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="30" Tween="False" Value="255" />
          <IntFrame FrameIndex="60" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="70" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="In" StartIndex="0" EndIndex="30">
          <RenderColor A="255" R="152" G="251" B="152" />
        </AnimationInfo>
        <AnimationInfo Name="Out" StartIndex="60" EndIndex="70">
          <RenderColor A="255" R="47" G="79" B="79" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="2054" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
          <AbstractNodeData Name="Panel_home" ActionTag="2015859816" Alpha="0" Tag="2071" IconVisible="False" PercentWidthEnable="True" PercentWidthEnabled="True" VerticalEdge="TopEdge" LeftMargin="-0.0015" RightMargin="0.0015" TopMargin="0.0005" BottomMargin="-0.0005" StretchHeightEnable="True" ClipAble="False" ColorAngle="90.0000" LeftEage="429" RightEage="429" TopEage="633" BottomEage="633" Scale9OriginX="-429" Scale9OriginY="-633" Scale9Width="858" Scale9Height="1266" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1920.0000" />
            <Children>
              <AbstractNodeData Name="Image_1" ActionTag="824074017" Tag="5778" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="200.0000" RightMargin="200.0000" TopMargin="1228.8960" BottomMargin="456.2880" StretchHeightEnable="True" Scale9Enable="True" LeftEage="60" RightEage="60" TopEage="48" BottomEage="6" Scale9OriginX="60" Scale9OriginY="48" Scale9Width="62" Scale9Height="94" ctype="ImageViewObjectData">
                <Size X="680.0000" Y="234.8160" />
                <Children>
                  <AbstractNodeData Name="Button_start" ActionTag="-120699189" Tag="2109" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="90.0000" RightMargin="90.0000" TopMargin="21.2587" BottomMargin="63.5568" TouchEnable="True" StretchHeightEnable="True" FontSize="14" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="43" BottomEage="49" Scale9OriginX="90" Scale9OriginY="43" Scale9Width="91" Scale9Height="30" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="500.0000" Y="150.0005" />
                    <Children>
                      <AbstractNodeData Name="Text_start" ActionTag="1479976661" Tag="2110" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="175.0000" RightMargin="175.0000" TopMargin="43.5002" BottomMargin="46.5003" FontSize="60" LabelText="START" ShadowOffsetX="0.0000" ShadowOffsetY="-4.0000" ctype="TextObjectData">
                        <Size X="150.0000" Y="60.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="250.0000" Y="76.5003" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5100" />
                        <PreSize X="0.3000" Y="0.4000" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="0" G="0" B="0" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_level" ActionTag="2042883128" Tag="17" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="519.2659" RightMargin="-150.7341" TopMargin="13.7156" BottomMargin="-4.2844" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="45" RightEage="45" TopEage="57" BottomEage="62" Scale9OriginX="-45" Scale9OriginY="-62" Scale9Width="90" Scale9Height="119" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="131.4681" Y="140.5693" />
                        <Children>
                          <AbstractNodeData Name="card_l0_1" ActionTag="1082599829" Alpha="203" Tag="13979" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="36.0313" RightMargin="54.4368" TopMargin="12.3309" BottomMargin="88.2384" ctype="SpriteObjectData">
                            <Size X="41.0000" Y="40.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="56.5313" Y="108.2384" />
                            <Scale ScaleX="1.4000" ScaleY="1.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.4300" Y="0.7700" />
                            <PreSize X="0.3119" Y="0.2846" />
                            <FileData Type="PlistSubImage" Path="card_l0.png" Plist="ui.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="card_l0_1_0_0" ActionTag="-796292845" Tag="13981" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="55.7515" RightMargin="34.7166" TopMargin="29.1993" BottomMargin="71.3700" ctype="SpriteObjectData">
                            <Size X="41.0000" Y="40.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="76.2515" Y="91.3700" />
                            <Scale ScaleX="1.6000" ScaleY="1.6000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.5800" Y="0.6500" />
                            <PreSize X="0.3119" Y="0.2846" />
                            <FileData Type="PlistSubImage" Path="card_l0.png" Plist="ui.plist" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_1" ActionTag="-427894801" Tag="13978" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="35.7340" RightMargin="35.7340" TopMargin="66.5302" BottomMargin="44.0391" FontSize="30" LabelText="More" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="60.0000" Y="30.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="65.7340" Y="59.0391" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="116" G="170" B="183" />
                            <PrePosition X="0.5000" Y="0.4200" />
                            <PreSize X="0.4564" Y="0.2134" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="585.0000" Y="66.0002" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="1.1700" Y="0.4400" />
                        <PreSize X="0.2629" Y="0.9371" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="340.0000" Y="138.5570" />
                    <Scale ScaleX="1.3000" ScaleY="1.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5901" />
                    <PreSize X="0.7353" Y="0.6388" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="PlistSubImage" Path="btn_yellow2.png" Plist="ui1.plist" />
                    <PressedFileData Type="PlistSubImage" Path="btn_yellow1.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="btn_yellow0.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="540.0000" Y="573.6960" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2988" />
                <PreSize X="0.6296" Y="0.1223" />
                <FileData Type="PlistSubImage" Path="Ui_Preview3.png" Plist="ui.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Panel_root" ActionTag="-45192823" Tag="2821" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="-0.0015" RightMargin="0.0015" TopMargin="-0.0005" BottomMargin="0.0005" StretchHeightEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="1080.0000" Y="1920.0000" />
                <Children>
                  <AbstractNodeData Name="Text_title" ActionTag="-442773380" VisibleForFrame="False" Tag="2822" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="457.1920" RightMargin="462.8080" TopMargin="1776.5439" BottomMargin="103.4560" FontSize="40" LabelText="赢得积分" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="160.0000" Y="40.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="537.1920" Y="123.4560" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="25" G="37" B="47" />
                    <PrePosition X="0.4974" Y="0.0643" />
                    <PreSize X="0.1481" Y="0.0208" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_btn_Level0_23" ActionTag="-846180279" Tag="2823" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="517.0000" RightMargin="517.0000" TopMargin="706.6000" BottomMargin="1167.4000" ctype="SpriteObjectData">
                    <Size X="46.0000" Y="46.0000" />
                    <Children>
                      <AbstractNodeData Name="Sprite_level_icon" ActionTag="-1763968584" Tag="14445" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" TopMargin="-1.8400" BottomMargin="1.8400" ctype="SpriteObjectData">
                        <Size X="46.0000" Y="46.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="23.0000" Y="24.8400" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5400" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="540.0000" Y="1190.4000" />
                    <Scale ScaleX="2.0000" ScaleY="2.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.6200" />
                    <PreSize X="0.0426" Y="0.0240" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_complete" ActionTag="1536673306" Tag="2834" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="755.5320" RightMargin="225.4680" TopMargin="619.6200" BottomMargin="1201.3800" ctype="SpriteObjectData">
                    <Size X="99.0000" Y="99.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="805.0320" Y="1250.8800" />
                    <Scale ScaleX="0.2344" ScaleY="0.2344" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.7454" Y="0.6515" />
                    <PreSize X="0.0917" Y="0.0516" />
                    <FileData Type="PlistSubImage" Path="Level_complete.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_5" ActionTag="-1331266871" Tag="79" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="310.0000" TopMargin="1029.3120" BottomMargin="825.6000" StretchHeightEnable="True" LeftEage="72" RightEage="72" TopEage="55" Scale9OriginX="72" Scale9OriginY="55" Scale9Width="77" Scale9Height="1" ctype="ImageViewObjectData">
                    <Size X="230.0000" Y="65.0880" />
                    <Children>
                      <AbstractNodeData Name="Image_5_0" ActionTag="-1210803339" Tag="80" IconVisible="False" LeftMargin="-0.0011" RightMargin="0.0011" TopMargin="0.0912" BottomMargin="-0.0001" StretchHeightEnable="True" FlipY="True" LeftEage="72" RightEage="73" TopEage="16" BottomEage="35" Scale9OriginX="72" Scale9OriginY="16" Scale9Width="76" Scale9Height="5" ctype="ImageViewObjectData">
                        <Size X="230.0000" Y="64.9969" />
                        <AnchorPoint />
                        <Position X="-0.0011" Y="-0.0001" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.0000" Y="0.0000" />
                        <PreSize X="1.0000" Y="0.9986" />
                        <FileData Type="PlistSubImage" Path="ui_ho2.png" Plist="ui.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_5_0" ActionTag="272798903" Tag="81" IconVisible="False" TopMargin="0.0911" StretchHeightEnable="True" FlipX="True" LeftEage="72" RightEage="72" TopEage="55" Scale9OriginX="72" Scale9OriginY="55" Scale9Width="77" Scale9Height="1" ctype="ImageViewObjectData">
                        <Size X="230.0000" Y="64.9969" />
                        <Children>
                          <AbstractNodeData Name="Image_5_0" ActionTag="-604071432" Tag="82" IconVisible="False" TopMargin="0.0000" StretchHeightEnable="True" FlipY="True" LeftEage="72" RightEage="72" BottomEage="55" Scale9OriginX="72" Scale9Width="77" Scale9Height="1" ctype="ImageViewObjectData">
                            <Size X="230.0000" Y="64.9969" />
                            <AnchorPoint />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="1.0000" Y="1.0000" />
                            <FileData Type="PlistSubImage" Path="ui_ho2.png" Plist="ui.plist" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="1.0000" Y="0.9986" />
                        <FileData Type="PlistSubImage" Path="ui_ho2.png" Plist="ui.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_level" ActionTag="-1805346380" Tag="2836" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.5000" RightMargin="206.5000" TopMargin="20.0880" BottomMargin="-45.0000" LabelText="1" ctype="TextBMFontObjectData">
                        <Size X="47.0000" Y="90.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.2043" Y="1.3827" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_Mission" ActionTag="-1077649113" Tag="2107" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-165.0000" RightMargin="65.0000" TopMargin="-69.0528" BottomMargin="74.1408" FontSize="60" LabelText="Mission 1-1" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="330.0000" Y="60.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="104.1408" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="238" B="179" />
                        <PrePosition Y="1.6000" />
                        <PreSize X="1.4348" Y="0.9218" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="540.0000" Y="825.6000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.4300" />
                    <PreSize X="0.2130" Y="0.0339" />
                    <FileData Type="PlistSubImage" Path="ui_ho2.png" Plist="ui.plist" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                <Position X="539.9985" Y="1920.0005" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="1.0000" />
                <PreSize X="1.0000" Y="1.0000" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="539.9985" Y="1919.9995" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="1.0000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="53" G="83" B="115" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>