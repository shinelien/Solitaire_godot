<GameFile>
  <PropertyGroup Name="2020HomeView_Mission_pad" Type="Layer" ID="34bef663-bd5b-45f3-88b4-ab74c8354c73" Version="3.10.0.0" />
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
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Panel_home" ActionTag="2015859816" Tag="2071" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" VerticalEdge="TopEdge" LeftMargin="-0.0015" RightMargin="0.0015" TopMargin="0.0005" BottomMargin="-0.0005" ClipAble="False" ColorAngle="90.0000" LeftEage="429" RightEage="429" TopEage="633" BottomEage="633" Scale9OriginX="-429" Scale9OriginY="-633" Scale9Width="858" Scale9Height="1266" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <Children>
              <AbstractNodeData Name="Image_1" ActionTag="824074017" Tag="5778" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="200.0000" RightMargin="200.0000" TopMargin="902.4000" BottomMargin="297.6000" StretchHeightEnable="True" Scale9Enable="True" LeftEage="60" RightEage="60" TopEage="48" BottomEage="6" Scale9OriginX="60" Scale9OriginY="48" Scale9Width="62" Scale9Height="94" ctype="ImageViewObjectData">
                <Size X="680.0000" Y="240.0000" />
                <Children>
                  <AbstractNodeData Name="Button_start" ActionTag="-120699189" Tag="2109" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="90.0000" RightMargin="90.0000" TopMargin="26.5440" BottomMargin="60.1440" TouchEnable="True" StretchHeightEnable="True" FontSize="14" Scale9Enable="True" LeftEage="90" RightEage="90" TopEage="43" BottomEage="49" Scale9OriginX="90" Scale9OriginY="43" Scale9Width="91" Scale9Height="30" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="500.0000" Y="153.3120" />
                    <Children>
                      <AbstractNodeData Name="Text_start" ActionTag="1479976661" Tag="2110" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="154.0000" RightMargin="154.0000" TopMargin="41.1228" BottomMargin="44.1892" FontSize="60" LabelText="START" ShadowOffsetX="0.0000" ShadowOffsetY="-4.0000" ctype="TextObjectData">
                        <Size X="192.0000" Y="68.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="250.0000" Y="78.1892" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5100" />
                        <PreSize X="0.3840" Y="0.4435" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="0" G="0" B="0" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_level" ActionTag="2042883128" Tag="17" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="519.2659" RightMargin="-150.7341" TopMargin="15.5700" BottomMargin="-2.8273" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="45" RightEage="45" TopEage="57" BottomEage="62" Scale9OriginX="45" Scale9OriginY="57" Scale9Width="115" Scale9Height="86" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
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
                          <AbstractNodeData Name="Text_1" ActionTag="-427894801" Tag="13978" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="31.2340" RightMargin="31.2340" TopMargin="64.5302" BottomMargin="42.0391" FontSize="30" LabelText="More" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="69.0000" Y="34.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="65.7340" Y="59.0391" />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="116" G="170" B="183" />
                            <PrePosition X="0.5000" Y="0.4200" />
                            <PreSize X="0.5248" Y="0.2419" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="585.0000" Y="67.4573" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="1.1700" Y="0.4400" />
                        <PreSize X="0.2629" Y="0.9169" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                        <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                        <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="340.0000" Y="136.8000" />
                    <Scale ScaleX="1.3000" ScaleY="1.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5700" />
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
                <Position X="540.0000" Y="417.6000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2900" />
                <PreSize X="0.6296" Y="0.1667" />
                <FileData Type="PlistSubImage" Path="Ui_Preview3.png" Plist="ui.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="Panel_root" ActionTag="-45192823" Tag="2821" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="-0.0015" RightMargin="0.0015" TopMargin="-0.0005" BottomMargin="0.0005" StretchHeightEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="1080.0000" Y="1440.0000" />
                <Children>
                  <AbstractNodeData Name="Text_title" ActionTag="-442773380" VisibleForFrame="False" Tag="2822" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="457.1920" RightMargin="462.8080" TopMargin="1324.9080" BottomMargin="70.0920" FontSize="40" LabelText="赢得积分" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="160.0000" Y="45.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="537.1920" Y="92.5920" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="25" G="37" B="47" />
                    <PrePosition X="0.4974" Y="0.0643" />
                    <PreSize X="0.1481" Y="0.0313" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_btn_Level0_23" ActionTag="-846180279" Tag="2823" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="439.3760" RightMargin="434.6240" TopMargin="486.1120" BottomMargin="745.8880" ctype="SpriteObjectData">
                    <Size X="206.0000" Y="208.0000" />
                    <Children>
                      <AbstractNodeData Name="Sprite_level_icon" ActionTag="-1763968584" Tag="14445" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="9.0000" RightMargin="9.0000" TopMargin="5.6800" BottomMargin="22.3200" ctype="SpriteObjectData">
                        <Size X="188.0000" Y="180.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="103.0000" Y="112.3200" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5400" />
                        <PreSize X="0.9126" Y="0.8654" />
                        <FileData Type="PlistSubImage" Path="Level_icon6.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="542.3760" Y="849.8880" />
                    <Scale ScaleX="1.5000" ScaleY="1.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5022" Y="0.5902" />
                    <PreSize X="0.1907" Y="0.1444" />
                    <FileData Type="PlistSubImage" Path="Level_btn_Level0.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Level_complete" ActionTag="1536673306" Tag="2834" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="755.5320" RightMargin="225.4680" TopMargin="452.3400" BottomMargin="888.6600" ctype="SpriteObjectData">
                    <Size X="99.0000" Y="99.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="805.0320" Y="938.1600" />
                    <Scale ScaleX="0.2344" ScaleY="0.2344" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.7454" Y="0.6515" />
                    <PreSize X="0.0917" Y="0.0688" />
                    <FileData Type="PlistSubImage" Path="Level_complete.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_5" ActionTag="-1331266871" Tag="79" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="310.0000" TopMargin="810.8640" BottomMargin="580.3200" StretchHeightEnable="True" LeftEage="72" RightEage="72" TopEage="55" Scale9OriginX="72" Scale9OriginY="55" Scale9Width="77" Scale9Height="1" ctype="ImageViewObjectData">
                    <Size X="230.0000" Y="48.8160" />
                    <Children>
                      <AbstractNodeData Name="Image_5_0" ActionTag="-1210803339" Tag="80" IconVisible="False" LeftMargin="-0.0011" RightMargin="0.0011" TopMargin="0.0684" BottomMargin="-0.0001" StretchHeightEnable="True" FlipY="True" LeftEage="72" RightEage="73" TopEage="16" BottomEage="35" Scale9OriginX="72" Scale9OriginY="16" Scale9Width="76" Scale9Height="5" ctype="ImageViewObjectData">
                        <Size X="230.0000" Y="48.7477" />
                        <AnchorPoint />
                        <Position X="-0.0011" Y="-0.0001" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="1.0000" Y="0.9986" />
                        <FileData Type="PlistSubImage" Path="ui_ho2.png" Plist="ui.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_5_0" ActionTag="272798903" Tag="81" IconVisible="False" TopMargin="0.0683" StretchHeightEnable="True" FlipX="True" LeftEage="72" RightEage="72" TopEage="55" Scale9OriginX="72" Scale9OriginY="55" Scale9Width="77" Scale9Height="1" ctype="ImageViewObjectData">
                        <Size X="230.0000" Y="48.7477" />
                        <Children>
                          <AbstractNodeData Name="Image_5_0" ActionTag="-604071432" Tag="82" IconVisible="False" StretchHeightEnable="True" FlipY="True" LeftEage="72" RightEage="72" BottomEage="55" Scale9OriginX="72" Scale9Width="77" Scale9Height="1" ctype="ImageViewObjectData">
                            <Size X="230.0000" Y="48.7477" />
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
                      <AbstractNodeData Name="Text_level" ActionTag="-1805346380" Tag="2836" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.5000" RightMargin="206.5000" TopMargin="3.8160" BottomMargin="-45.0000" LabelText="1" ctype="TextBMFontObjectData">
                        <Size X="47.0000" Y="90.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition />
                        <PreSize X="0.2043" Y="1.8437" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Text_Mission" ActionTag="-1077649113" Tag="2107" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-153.5000" RightMargin="76.5000" TopMargin="-63.2896" BottomMargin="44.1056" FontSize="60" LabelText="Mission 1-1" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="307.0000" Y="68.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position Y="78.1056" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="238" B="179" />
                        <PrePosition Y="1.6000" />
                        <PreSize X="1.3348" Y="1.3930" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="540.0000" Y="580.3200" />
                    <Scale ScaleX="0.8000" ScaleY="0.8000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.4030" />
                    <PreSize X="0.2130" Y="0.0339" />
                    <FileData Type="PlistSubImage" Path="ui_ho2.png" Plist="ui.plist" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                <Position X="539.9985" Y="1440.0005" />
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
            <Position X="539.9985" Y="1439.9995" />
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