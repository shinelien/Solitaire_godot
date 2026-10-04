<GameFile>
  <PropertyGroup Name="banner_pad" Type="Node" ID="aa636998-0399-44dd-a01b-eaa8fceb830d" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="25" Speed="1.0000" ActivedAnimationName="start">
        <Timeline ActionTag="-118006864" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.2000" Y="1.2000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.5000" Y="1.5000">
            <EasingData Type="1" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="1.2000" Y="1.2000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="85" G="107" B="47" />
        </AnimationInfo>
        <AnimationInfo Name="idle" StartIndex="0" EndIndex="0">
          <RenderColor A="255" R="255" G="99" B="71" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="266" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image_banner" ActionTag="-1911853260" Tag="1977" IconVisible="False" LeftMargin="-541.0999" RightMargin="-540.9001" TopMargin="-179.0000" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1082.0000" Y="179.0000" />
            <Children>
              <AbstractNodeData Name="Node_LimitScore" ActionTag="-1730179097" Tag="1979" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="541.0000" RightMargin="541.0000" TopMargin="107.4000" BottomMargin="71.6000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Node_score" ActionTag="88742243" Tag="1980" IconVisible="True" TopMargin="11.0000" BottomMargin="-11.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position Y="-11.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_score1_32" Visible="False" ActionTag="1912219246" Tag="1981" IconVisible="False" LeftMargin="86.9375" RightMargin="-253.9375" TopMargin="-73.2882" BottomMargin="69.2882" ctype="SpriteObjectData">
                    <Size X="167.0000" Y="4.0000" />
                    <Children>
                      <AbstractNodeData Name="game_score1_32_0" ActionTag="-1214302115" Tag="1982" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-374.0800" RightMargin="374.0800" FlipX="True" ctype="SpriteObjectData">
                        <Size X="167.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-290.5800" Y="2.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.7400" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="170.4375" Y="71.2882" />
                    <Scale ScaleX="0.9000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_bannerScore" ActionTag="-162857814" Alpha="102" Tag="1983" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-53.5000" RightMargin="-53.5000" TopMargin="-88.2880" BottomMargin="54.2880" FontSize="30" LabelText="SCORE" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="107.0000" Y="34.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="71.2880" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="541.0000" Y="71.6000" />
                <Scale ScaleX="0.8400" ScaleY="0.8400" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4000" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_CollectPoker" ActionTag="1315168001" Tag="1984" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="541.0000" RightMargin="541.0000" TopMargin="107.4000" BottomMargin="71.6000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_3" ActionTag="1396663796" Tag="1985" IconVisible="False" RightMargin="-314.0000" TopMargin="-60.0000" BottomMargin="-80.0000" Scale9Enable="True" LeftEage="46" RightEage="46" TopEage="59" BottomEage="59" Scale9OriginX="46" Scale9OriginY="59" Scale9Width="191" Scale9Height="40" ctype="ImageViewObjectData">
                    <Size X="314.0000" Y="140.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_3_0" ActionTag="2064107914" Tag="1986" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="0.0001" RightMargin="-0.0001" FlipX="True" Scale9Enable="True" LeftEage="46" RightEage="46" TopEage="59" BottomEage="59" Scale9OriginX="46" Scale9OriginY="59" Scale9Width="191" Scale9Height="40" ctype="ImageViewObjectData">
                        <Size X="314.0000" Y="140.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="0.0001" Y="70.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.0000" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="level_Collect0.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_tips" Visible="False" ActionTag="1618740833" VisibleForFrame="False" Tag="1987" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="215.3928" RightMargin="-1.3928" TopMargin="20.0000" BottomMargin="20.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="78" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="100.0000" Y="100.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="265.3928" Y="70.0000" />
                        <Scale ScaleX="0.8000" ScaleY="0.8000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.8452" Y="0.5000" />
                        <PreSize X="0.3185" Y="0.7143" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="level_Collect_btn1.png" Plist="ui1.plist" />
                        <PressedFileData Type="PlistSubImage" Path="level_Collect_btn1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="level_Collect_btn0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_1" ActionTag="-1785328569" Tag="1988" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-58.6238" RightMargin="372.6238" TopMargin="71.5680" BottomMargin="68.4320" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_card1" ActionTag="149879328" Tag="1989" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_card1" ActionTag="-1279637881" VisibleForFrame="False" Tag="1990" IconVisible="False" LeftMargin="-20.0000" RightMargin="-80.0000" TopMargin="-5.0000" BottomMargin="-85.0000" LabelText="10" ctype="TextBMFontObjectData">
                            <Size X="100.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="30.0000" Y="-40.0000" />
                            <Scale ScaleX="0.4000" ScaleY="0.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="-58.6238" Y="68.4320" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-0.1867" Y="0.4888" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_2" ActionTag="1932545043" Tag="1991" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="58.6238" RightMargin="255.3762" TopMargin="71.5680" BottomMargin="68.4320" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_card2" ActionTag="906782717" Tag="1992" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_card2" ActionTag="-2000044483" VisibleForFrame="False" Tag="1993" IconVisible="False" LeftMargin="-20.0000" RightMargin="-80.0000" TopMargin="-5.0000" BottomMargin="-85.0000" LabelText="10" ctype="TextBMFontObjectData">
                            <Size X="100.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="30.0000" Y="-40.0000" />
                            <Scale ScaleX="0.4000" ScaleY="0.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="58.6238" Y="68.4320" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1867" Y="0.4888" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_3" ActionTag="-1982602230" Tag="1994" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-175.8400" RightMargin="489.8400" TopMargin="70.0000" BottomMargin="70.0000" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_card3" ActionTag="-697668106" Tag="1995" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_card3" ActionTag="-2083685228" VisibleForFrame="False" Tag="1996" IconVisible="False" LeftMargin="-25.0000" RightMargin="-75.0000" TopMargin="-5.0000" BottomMargin="-85.0000" LabelText="10" ctype="TextBMFontObjectData">
                            <Size X="100.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="25.0000" Y="-40.0000" />
                            <Scale ScaleX="0.4000" ScaleY="0.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="-175.8400" Y="70.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-0.5600" Y="0.5000" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_4" ActionTag="-944650926" Tag="1997" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="175.8400" RightMargin="138.1600" TopMargin="70.0000" BottomMargin="70.0000" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_card4" ActionTag="-134553095" Tag="1998" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_card4" ActionTag="244170427" VisibleForFrame="False" Tag="1999" IconVisible="False" LeftMargin="-25.0000" RightMargin="-75.0000" TopMargin="-5.0000" BottomMargin="-85.0000" LabelText="10" ctype="TextBMFontObjectData">
                            <Size X="100.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="25.0000" Y="-40.0000" />
                            <Scale ScaleX="0.4000" ScaleY="0.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="175.8400" Y="70.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5600" Y="0.5000" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="0.5000" />
                    <Position Y="-10.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="level_Collect0.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_6" ActionTag="-1910177209" Tag="2000" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_score1_32" ActionTag="1568536007" Tag="2001" IconVisible="False" LeftMargin="86.9375" RightMargin="-253.9375" TopMargin="-73.2882" BottomMargin="69.2882" ctype="SpriteObjectData">
                    <Size X="167.0000" Y="4.0000" />
                    <Children>
                      <AbstractNodeData Name="game_score1_32_0" ActionTag="-1863546469" Tag="2002" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-374.0800" RightMargin="374.0800" FlipX="True" ctype="SpriteObjectData">
                        <Size X="167.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-290.5800" Y="2.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.7400" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="170.4375" Y="71.2882" />
                    <Scale ScaleX="0.9000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_bannerCollet" ActionTag="-198469298" Alpha="102" Tag="2003" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-69.5000" RightMargin="-69.5000" TopMargin="-88.2880" BottomMargin="54.2880" FontSize="30" LabelText="COLLECT" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="139.0000" Y="34.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="71.2880" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="541.0000" Y="71.6000" />
                <Scale ScaleX="0.8400" ScaleY="0.8400" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4000" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_TargetPoker" ActionTag="-690732189" Tag="2004" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="541.0000" RightMargin="541.0000" TopMargin="107.4000" BottomMargin="71.6000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_3" ActionTag="-1714628981" Tag="2005" IconVisible="False" RightMargin="-283.0000" TopMargin="-60.0000" BottomMargin="-80.0000" Scale9Enable="True" LeftEage="46" RightEage="46" TopEage="59" BottomEage="59" Scale9OriginX="46" Scale9OriginY="59" Scale9Width="191" Scale9Height="40" ctype="ImageViewObjectData">
                    <Size X="283.0000" Y="140.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_3_0" ActionTag="716203409" Tag="2006" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="0.0001" RightMargin="-0.0001" FlipX="True" Scale9Enable="True" LeftEage="46" RightEage="46" TopEage="59" BottomEage="59" Scale9OriginX="46" Scale9OriginY="59" Scale9Width="191" Scale9Height="40" ctype="ImageViewObjectData">
                        <Size X="283.0000" Y="140.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="0.0001" Y="70.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.0000" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="level_Collect0.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_tips" Visible="False" ActionTag="496705135" VisibleForFrame="False" Tag="2007" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="199.0400" RightMargin="-16.0400" TopMargin="20.0000" BottomMargin="20.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="78" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="100.0000" Y="100.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="249.0400" Y="70.0000" />
                        <Scale ScaleX="0.9000" ScaleY="0.9000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.8800" Y="0.5000" />
                        <PreSize X="0.3534" Y="0.7143" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="level_Collect_btn1.png" Plist="ui1.plist" />
                        <PressedFileData Type="PlistSubImage" Path="level_Collect_btn1.png" Plist="ui1.plist" />
                        <NormalFileData Type="PlistSubImage" Path="level_Collect_btn0.png" Plist="ui1.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_Target1" ActionTag="238282997" Tag="2008" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="283.0000" TopMargin="71.4000" BottomMargin="68.6000" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_cardTarget1" ActionTag="-507633273" Tag="2009" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_cardTarget1" ActionTag="1912696327" Tag="2010" IconVisible="False" LeftMargin="38.0696" RightMargin="-88.0696" TopMargin="-27.9872" BottomMargin="-16.0128" LabelText="12" ctype="TextBMFontObjectData">
                                <Size X="96.0000" Y="90.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="86.0696" Y="28.9872" />
                                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="1.8711" Y="0.6302" />
                                <PreSize X="2.0870" Y="1.9565" />
                                <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position Y="68.6000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition Y="0.4900" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="0.5000" />
                    <Position Y="-10.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="level_Collect0.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_score1_32" ActionTag="-693650407" Tag="2011" IconVisible="False" LeftMargin="86.9375" RightMargin="-253.9375" TopMargin="-73.2882" BottomMargin="69.2882" ctype="SpriteObjectData">
                    <Size X="167.0000" Y="4.0000" />
                    <Children>
                      <AbstractNodeData Name="game_score1_32_0" ActionTag="1881235681" Tag="2012" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-374.0800" RightMargin="374.0800" FlipX="True" ctype="SpriteObjectData">
                        <Size X="167.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-290.5800" Y="2.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.7400" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="170.4375" Y="71.2882" />
                    <Scale ScaleX="0.9000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_bannerTarget" ActionTag="590539865" Alpha="102" Tag="2013" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-69.5000" RightMargin="-69.5000" TopMargin="-88.2882" BottomMargin="54.2882" FontSize="30" LabelText="COLLECT" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="139.0000" Y="34.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="71.2882" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="541.0000" Y="71.6000" />
                <Scale ScaleX="0.8400" ScaleY="0.8400" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4000" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_LimitTime" ActionTag="639133109" Tag="2014" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="541.0000" RightMargin="541.0000" TopMargin="107.4000" BottomMargin="71.6000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="game_time0_1" ActionTag="162988696" Tag="2015" IconVisible="False" LeftMargin="-330.0000" RightMargin="282.0000" TopMargin="-15.0000" BottomMargin="-33.0000" ctype="SpriteObjectData">
                    <Size X="48.0000" Y="48.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-306.0000" Y="-9.0000" />
                    <Scale ScaleX="1.3000" ScaleY="1.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_time0.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_score1_32" ActionTag="404313209" Tag="2016" IconVisible="False" LeftMargin="86.9375" RightMargin="-253.9375" TopMargin="-73.2882" BottomMargin="69.2882" ctype="SpriteObjectData">
                    <Size X="167.0000" Y="4.0000" />
                    <Children>
                      <AbstractNodeData Name="game_score1_32_0" ActionTag="1496090090" Tag="2017" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-374.0800" RightMargin="374.0800" FlipX="True" ctype="SpriteObjectData">
                        <Size X="167.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-290.5800" Y="2.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.7400" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="170.4375" Y="71.2882" />
                    <Scale ScaleX="0.9000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_bannerTime" ActionTag="-1185051245" Alpha="102" Tag="2018" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-36.0000" RightMargin="-36.0000" TopMargin="-88.2880" BottomMargin="54.2880" FontSize="30" LabelText="TIME" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="72.0000" Y="34.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="71.2880" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_bannerTime" ActionTag="149477325" Tag="2019" IconVisible="True" TopMargin="11.0000" BottomMargin="-11.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position Y="-11.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="541.0000" Y="71.6000" />
                <Scale ScaleX="0.8400" ScaleY="0.8400" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4000" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_bannerScore" ActionTag="1233033040" Tag="2020" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="97.3800" RightMargin="984.6200" TopMargin="110.9800" BottomMargin="68.0200" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_moveBg" ActionTag="-1068793734" Alpha="203" Tag="137" IconVisible="False" LeftMargin="-78.5218" RightMargin="-86.5218" TopMargin="-61.7391" BottomMargin="-61.7391" Scale9Enable="True" LeftEage="30" RightEage="30" TopEage="33" BottomEage="33" Scale9OriginX="30" Scale9OriginY="33" Scale9Width="32" Scale9Height="34" ctype="ImageViewObjectData">
                    <Size X="165.0435" Y="123.4782" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="4.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_btn_S2.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_bannerTargetMoveNum" ActionTag="-118006864" Tag="2021" IconVisible="False" LeftMargin="-3.4499" RightMargin="-63.5501" TopMargin="-31.7071" BottomMargin="-28.2929" LabelText="150" ctype="TextBMFontObjectData">
                    <Size X="67.0000" Y="60.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="-3.4499" Y="1.7071" />
                    <Scale ScaleX="1.2000" ScaleY="1.2000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num12x.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_moves0_63" ActionTag="286447207" Tag="2022" IconVisible="False" LeftMargin="-61.9520" RightMargin="16.9520" TopMargin="-22.7069" BottomMargin="-19.2931" ctype="SpriteObjectData">
                    <Size X="45.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-39.4520" Y="1.7069" />
                    <Scale ScaleX="1.1000" ScaleY="1.1000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_moves0.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="97.3800" Y="68.0200" />
                <Scale ScaleX="0.8400" ScaleY="0.8400" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0900" Y="0.3800" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="-541.0999" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="FileNode_1" ActionTag="-433430187" Tag="2625" IconVisible="True" LeftMargin="72.3434" RightMargin="-72.3434" TopMargin="46.9244" BottomMargin="-46.9244" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="0.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="72.3434" Y="-46.9244" />
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