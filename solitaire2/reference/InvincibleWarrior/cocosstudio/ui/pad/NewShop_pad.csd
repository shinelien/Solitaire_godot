<GameFile>
  <PropertyGroup Name="NewShop_pad" Type="Layer" ID="104c37cd-6559-486f-aad9-5a76c74243cc" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="25" Speed="1.0000" ActivedAnimationName="Start">
        <Timeline ActionTag="294280812" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="15" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1005399743" Property="Alpha">
          <IntFrame FrameIndex="6" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="12" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-210907619" Property="Alpha">
          <IntFrame FrameIndex="6" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="12" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="199580910" Property="Position">
          <PointFrame FrameIndex="0" X="540.0000" Y="400.0000">
            <EasingData Type="8" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="540.0000" Y="550.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1315137066" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="11" />
          </IntFrame>
          <IntFrame FrameIndex="5" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="105" G="105" B="105" />
        </AnimationInfo>
        <AnimationInfo Name="out" StartIndex="60" EndIndex="100">
          <RenderColor A="255" R="147" G="112" B="219" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="78" ctype="GameLayerObjectData">
        <Size X="1080.0000" Y="1440.0000" />
        <Children>
          <AbstractNodeData Name="Panel_1" ActionTag="294280812" Alpha="0" Tag="374" IconVisible="False" LeftMargin="0.0010" RightMargin="-0.0010" TouchEnable="True" ClipAble="False" BackColorAlpha="76" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <AnchorPoint />
            <Position X="0.0010" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="panel_shop" ActionTag="-1315137066" Alpha="0" Tag="23" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" LeftEage="409" RightEage="409" TopEage="728" BottomEage="728" Scale9OriginX="-409" Scale9OriginY="-728" Scale9Width="818" Scale9Height="1456" ctype="PanelObjectData">
            <Size X="1080.0000" Y="1440.0000" />
            <Children>
              <AbstractNodeData Name="Panel_out" ActionTag="-1664370828" Tag="478" IconVisible="False" LeftMargin="206.3205" RightMargin="204.6517" TopMargin="548.9850" BottomMargin="67.8229" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="669.0278" Y="823.1921" />
                <AnchorPoint />
                <Position X="206.3205" Y="67.8229" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1910" Y="0.0471" />
                <PreSize X="0.6195" Y="0.5717" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_2" ActionTag="199580910" Tag="404" IconVisible="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="1040.0000" BottomMargin="400.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_7" Visible="False" ActionTag="-1005399743" Alpha="0" Tag="405" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-529.5000" RightMargin="-529.5000" TopMargin="-642.0007" BottomMargin="-491.6409" Scale9Enable="True" LeftEage="124" RightEage="124" TopEage="70" BottomEage="182" Scale9OriginX="124" Scale9OriginY="70" Scale9Width="48" Scale9Height="153" ctype="ImageViewObjectData">
                    <Size X="1059.0000" Y="1133.6416" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position Y="642.0007" />
                    <Scale ScaleX="1.0000" ScaleY="1.2000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="main_table1.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_11" ActionTag="-210907619" Alpha="0" Tag="449" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-521.9661" RightMargin="-521.9661" TopMargin="-635.7714" BottomMargin="-691.7125" Scale9Enable="True" LeftEage="97" RightEage="97" TopEage="133" BottomEage="133" Scale9OriginX="97" Scale9OriginY="133" Scale9Width="102" Scale9Height="139" ctype="ImageViewObjectData">
                    <Size X="1043.9321" Y="1327.4839" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position Y="635.7714" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="main_table1.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_detail2_15" ActionTag="-722402238" Tag="406" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-125.0000" RightMargin="-125.0000" TopMargin="-634.5002" BottomMargin="593.5002" ctype="SpriteObjectData">
                    <Size X="250.0000" Y="41.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="614.0002" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_detail2.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_detail2_15_0" ActionTag="-2018235678" Tag="407" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-125.0000" RightMargin="-125.0000" TopMargin="-634.5002" BottomMargin="593.5002" ctype="SpriteObjectData">
                    <Size X="250.0000" Y="41.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="614.0002" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_detail2.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_1" ActionTag="-1762025381" Tag="408" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-465.0000" TopMargin="-452.9999" BottomMargin="-557.0001" LeftEage="153" RightEage="153" TopEage="389" BottomEage="389" Scale9OriginX="153" Scale9OriginY="389" Scale9Width="159" Scale9Height="402" ctype="ImageViewObjectData">
                    <Size X="465.0000" Y="1010.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_1_0" ActionTag="1897940054" Tag="409" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" FlipX="True" LeftEage="153" RightEage="153" TopEage="389" BottomEage="389" Scale9OriginX="153" Scale9OriginY="389" Scale9Width="159" Scale9Height="402" ctype="ImageViewObjectData">
                        <Size X="465.0000" Y="1010.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                        <Position X="465.0000" Y="505.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="1.0000" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position Y="452.9999" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg1_9_1" Visible="False" ActionTag="674838967" VisibleForFrame="False" Tag="410" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-44.0000" RightMargin="-44.0000" TopMargin="441.0002" BottomMargin="-557.0002" FlipY="True" ctype="SpriteObjectData">
                    <Size X="88.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="0.5000" />
                    <Position Y="-557.0002" />
                    <Scale ScaleX="10.5531" ScaleY="0.5575" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="ListView_bg" ActionTag="-219074175" Tag="1548" IconVisible="False" LeftMargin="-452.5040" RightMargin="-451.4960" TopMargin="-454.0021" BottomMargin="-408.9979" TouchEnable="True" ClipAble="True" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" IsBounceEnabled="True" ScrollDirectionType="0" DirectionType="Vertical" ctype="ListViewObjectData">
                    <Size X="904.0000" Y="863.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position X="-0.5040" Y="454.0021" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <SingleColor A="255" R="150" G="150" B="255" />
                    <FirstColor A="255" R="150" G="150" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg1_9" ActionTag="767264961" Tag="412" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-44.0000" RightMargin="-44.0000" TopMargin="-453.0000" BottomMargin="337.0000" ctype="SpriteObjectData">
                    <Size X="88.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="395.0000" />
                    <Scale ScaleX="10.4024" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg1_9_0" ActionTag="1174245578" Tag="413" RotationSkewX="-90.0000" RotationSkewY="-90.0002" IconVisible="False" LeftMargin="377.0010" RightMargin="-465.0010" TopMargin="-712.0020" BottomMargin="596.0020" FlipY="True" ctype="SpriteObjectData">
                    <Size X="88.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="1.0000" />
                    <Position X="465.0010" Y="596.0020" />
                    <Scale ScaleX="11.4323" ScaleY="0.4700" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg1_9_0_0" ActionTag="-1076568179" Tag="414" RotationSkewX="-90.0000" RotationSkewY="-90.0002" IconVisible="False" LeftMargin="-553.0047" RightMargin="465.0047" TopMargin="-589.9937" BottomMargin="473.9937" ctype="SpriteObjectData">
                    <Size X="88.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position X="-465.0047" Y="589.9937" />
                    <Scale ScaleX="11.3721" ScaleY="0.4700" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game0_uibg1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg2_3_0" ActionTag="2037062734" Tag="415" IconVisible="False" LeftMargin="465.0001" RightMargin="-480.0001" TopMargin="-606.0010" BottomMargin="-849.9990" FlipX="True" ctype="SpriteObjectData">
                    <Size X="15.0000" Y="1456.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position X="480.0001" Y="606.0010" />
                    <Scale ScaleX="1.0000" ScaleY="0.8097" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg2_3" ActionTag="-884211945" Tag="416" IconVisible="False" LeftMargin="-479.9980" RightMargin="464.9980" TopMargin="-606.0013" BottomMargin="-849.9987" ctype="SpriteObjectData">
                    <Size X="15.0000" Y="1456.0000" />
                    <AnchorPoint ScaleY="1.0000" />
                    <Position X="-479.9980" Y="606.0013" />
                    <Scale ScaleX="1.0000" ScaleY="0.8097" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_2" ActionTag="1817447055" Tag="417" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-479.6677" RightMargin="-479.6677" TopMargin="-605.9995" BottomMargin="589.9995" Scale9Enable="True" LeftEage="315" RightEage="315" TopEage="5" BottomEage="5" Scale9OriginX="315" Scale9OriginY="5" Scale9Width="327" Scale9Height="6" ctype="ImageViewObjectData">
                    <Size X="959.3354" Y="16.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="597.9995" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_2_1" ActionTag="1026970198" Tag="418" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-475.8025" RightMargin="-475.8025" TopMargin="-469.0001" BottomMargin="453.0001" Scale9Enable="True" LeftEage="315" RightEage="315" TopEage="5" BottomEage="5" Scale9OriginX="315" Scale9OriginY="5" Scale9Width="327" Scale9Height="6" ctype="ImageViewObjectData">
                    <Size X="951.6050" Y="16.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="461.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game0_uibg9_14" ActionTag="630812367" Tag="419" IconVisible="False" LeftMargin="-474.0001" RightMargin="-477.9999" TopMargin="-597.5001" BottomMargin="464.5001" ctype="SpriteObjectData">
                    <Size X="952.0000" Y="133.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.9999" Y="531.0001" />
                    <Scale ScaleX="0.9922" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="img_btn_coin" ActionTag="88100711" Tag="421" IconVisible="False" LeftMargin="-469.0587" RightMargin="144.9413" TopMargin="-572.4038" BottomMargin="495.5960" TouchEnable="True" Scale9Enable="True" LeftEage="24" RightEage="24" TopEage="30" BottomEage="30" Scale9OriginX="24" Scale9OriginY="30" Scale9Width="4" Scale9Height="1" ctype="ImageViewObjectData">
                    <Size X="324.1173" Y="76.8078" />
                    <Children>
                      <AbstractNodeData Name="Image_7" ActionTag="1372464613" Tag="422" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-2.7596" RightMargin="223.4641" TopMargin="-17.1043" BottomMargin="-13.1866" LeftEage="20" RightEage="20" TopEage="20" BottomEage="20" Scale9OriginX="20" Scale9OriginY="20" Scale9Width="80" Scale9Height="80" ctype="ImageViewObjectData">
                        <Size X="103.4128" Y="107.0987" />
                        <AnchorPoint ScaleX="0.5081" ScaleY="0.4579" />
                        <Position X="49.7844" Y="35.8539" />
                        <Scale ScaleX="0.4000" ScaleY="0.4000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1536" Y="0.4668" />
                        <PreSize X="0.3191" Y="1.3944" />
                        <FileData Type="PlistSubImage" Path="gold/gold_0.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="atlasLabel_coin" ActionTag="197760475" VisibleForFrame="False" Tag="423" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-382.2269" RightMargin="636.3442" TopMargin="58.6523" BottomMargin="0.1555" CharWidth="14" CharHeight="18" LabelText="20000" StartChar="." ctype="TextAtlasObjectData">
                        <Size X="70.0000" Y="18.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-347.2269" Y="9.1555" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="0" />
                        <PrePosition X="-1.0713" Y="0.1192" />
                        <PreSize X="0.2160" Y="0.2344" />
                        <LabelAtlasFileImage_CNB Type="Default" Path="Default/TextAtlas.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_3" ActionTag="780280025" Alpha="102" Tag="4408" IconVisible="False" LeftMargin="255.3026" RightMargin="1.8147" TopMargin="2.8078" BottomMargin="1.1723" Scale9Enable="True" LeftEage="18" RightEage="18" TopEage="18" BottomEage="18" Scale9OriginX="18" Scale9OriginY="18" Scale9Width="20" Scale9Height="20" ctype="ImageViewObjectData">
                        <Size X="67.0000" Y="72.8277" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                        <Position X="322.3026" Y="74.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.9944" Y="0.9634" />
                        <PreSize X="0.2067" Y="0.9482" />
                        <FileData Type="PlistSubImage" Path="Level_win2.png" Plist="ui1.plist" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_add" ActionTag="1012382814" Tag="424" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="272.7885" RightMargin="19.3288" TopMargin="24.2181" BottomMargin="22.5897" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="22" Scale9Height="27" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="32.0000" Y="30.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="288.7885" Y="37.5897" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.8910" Y="0.4894" />
                        <PreSize X="0.0987" Y="0.3906" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <NormalFileData Type="Normal" Path="img/img_add.png" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="BitmapFontLabel_coin" ActionTag="185287474" Tag="425" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="76.0563" RightMargin="111.0610" TopMargin="7.5744" BottomMargin="9.2334" LabelText="20000" ctype="TextBMFontObjectData">
                        <Size X="137.0000" Y="60.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="144.5563" Y="39.2334" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.4460" Y="0.5108" />
                        <PreSize X="0.4227" Y="0.7812" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num12x.fnt" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-307.0000" Y="533.9999" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="Level_tips.png" Plist="ui1.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_detail1_17" ActionTag="-802651499" Tag="426" IconVisible="False" LeftMargin="434.0000" RightMargin="-475.0000" TopMargin="-596.9752" BottomMargin="472.9752" ctype="SpriteObjectData">
                    <Size X="41.0000" Y="124.0000" />
                    <Children>
                      <AbstractNodeData Name="game_detail0_16" ActionTag="-1180996647" Tag="427" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="37.1000" RightMargin="-12.1000" TopMargin="1.5000" BottomMargin="1.5000" ctype="SpriteObjectData">
                        <Size X="16.0000" Y="121.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="45.1000" Y="62.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="1.1000" Y="0.5000" />
                        <PreSize X="0.3902" Y="0.9758" />
                        <FileData Type="PlistSubImage" Path="game_detail0.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5002" />
                    <Position X="475.0000" Y="535.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_detail1.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Image_2_0" ActionTag="1426564668" Tag="428" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-478.5000" RightMargin="-478.5000" TopMargin="557.0002" BottomMargin="-573.0002" FlipY="True" LeftEage="315" RightEage="315" TopEage="5" BottomEage="5" Scale9OriginX="315" Scale9OriginY="5" Scale9Width="327" Scale9Height="6" ctype="ImageViewObjectData">
                    <Size X="957.0000" Y="16.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-565.0002" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_shop_close" ActionTag="1021498041" Tag="429" IconVisible="False" LeftMargin="405.3394" RightMargin="-525.3394" TopMargin="-657.5522" BottomMargin="537.5522" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="90" Scale9Height="98" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="120.0000" Y="120.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="465.3394" Y="597.5522" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_btn_close3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_btn_close2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_title" ActionTag="-431057936" Tag="32" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-103.0000" RightMargin="-103.0000" TopMargin="-565.0002" BottomMargin="497.0002" FontSize="60" LabelText="STORE" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="206.0000" Y="68.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="531.0002" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="200" B="138" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="105" G="68" B="27" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_tab3" ActionTag="-43368572" Tag="1" IconVisible="False" LeftMargin="-458.0000" RightMargin="153.0000" TopMargin="405.2259" BottomMargin="-551.2259" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="140" RightEage="125" TopEage="50" BottomEage="39" Scale9OriginX="140" Scale9OriginY="50" Scale9Width="40" Scale9Height="57" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="305.0000" Y="146.0000" />
                    <Children>
                      <AbstractNodeData Name="text_title1" ActionTag="-1157570446" Alpha="178" Tag="31" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="72.5000" RightMargin="72.5000" TopMargin="78.2400" BottomMargin="22.7600" FontSize="40" LabelText="纸牌背面" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="160.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="152.5000" Y="45.2600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="82" G="55" B="4" />
                        <PrePosition X="0.5000" Y="0.3100" />
                        <PreSize X="0.5246" Y="0.3082" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="storecard_1_2" ActionTag="319995000" Tag="954" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="128.5000" RightMargin="128.5000" TopMargin="23.2600" BottomMargin="78.7400" ctype="SpriteObjectData">
                        <Size X="48.0000" Y="44.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="152.5000" Y="100.7400" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.6900" />
                        <PreSize X="0.1574" Y="0.3014" />
                        <FileData Type="PlistSubImage" Path="storecard_1.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="-458.0000" Y="-478.2259" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_store_btn3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_store_btn2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_tab2" ActionTag="180524406" Tag="2" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-152.5000" RightMargin="-152.5000" TopMargin="405.2258" BottomMargin="-551.2258" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="275" Scale9Height="124" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="305.0000" Y="146.0000" />
                    <Children>
                      <AbstractNodeData Name="storecard_2_3" ActionTag="1508586547" Tag="955" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="121.0000" RightMargin="121.0000" TopMargin="14.7600" BottomMargin="70.2400" ctype="SpriteObjectData">
                        <Size X="63.0000" Y="61.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="152.5000" Y="100.7400" />
                        <Scale ScaleX="0.8500" ScaleY="0.8500" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.6900" />
                        <PreSize X="0.2066" Y="0.4178" />
                        <FileData Type="PlistSubImage" Path="storecard_2.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_title2" ActionTag="-39965726" Alpha="178" Tag="29" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="72.5000" RightMargin="72.5000" TopMargin="78.2400" BottomMargin="22.7600" FontSize="40" LabelText="纸牌正面" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="160.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="152.5000" Y="45.2600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="82" G="55" B="4" />
                        <PrePosition X="0.5000" Y="0.3100" />
                        <PreSize X="0.5246" Y="0.3082" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="-478.2258" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_store_btn3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_store_btn2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Button_tab1" ActionTag="1001682534" Alpha="249" Tag="3" IconVisible="False" LeftMargin="152.0000" RightMargin="-457.0000" TopMargin="405.2259" BottomMargin="-551.2259" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="275" Scale9Height="124" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="305.0000" Y="146.0000" />
                    <Children>
                      <AbstractNodeData Name="storecard_0_1" ActionTag="1516402342" Tag="953" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="121.0000" RightMargin="121.0000" TopMargin="13.2416" BottomMargin="71.7584" ctype="SpriteObjectData">
                        <Size X="63.0000" Y="61.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="152.5000" Y="102.2584" />
                        <Scale ScaleX="0.8000" ScaleY="0.8000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.7004" />
                        <PreSize X="0.2066" Y="0.4178" />
                        <FileData Type="PlistSubImage" Path="storecard_0.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="text_title3" ActionTag="437520541" Alpha="178" Tag="27" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="72.5000" RightMargin="72.5000" TopMargin="78.2400" BottomMargin="22.7600" FontSize="40" LabelText="游戏背景" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="160.0000" Y="45.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="152.5000" Y="45.2600" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="82" G="55" B="4" />
                        <PrePosition X="0.5000" Y="0.3100" />
                        <PreSize X="0.5246" Y="0.3082" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="457.0000" Y="-478.2259" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <PressedFileData Type="PlistSubImage" Path="ui_store_btn3.png" Plist="ui1.plist" />
                    <NormalFileData Type="PlistSubImage" Path="ui_store_btn2.png" Plist="ui1.plist" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_detail1_17_0" ActionTag="234711338" Tag="430" IconVisible="False" LeftMargin="-516.0000" RightMargin="475.0000" TopMargin="-596.9752" BottomMargin="472.9752" ctype="SpriteObjectData">
                    <Size X="41.0000" Y="124.0000" />
                    <Children>
                      <AbstractNodeData Name="game_detail0_16" ActionTag="-488149653" Tag="431" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="37.1000" RightMargin="-12.1000" TopMargin="1.5000" BottomMargin="1.5000" ctype="SpriteObjectData">
                        <Size X="16.0000" Y="121.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="45.1000" Y="62.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="1.1000" Y="0.5000" />
                        <PreSize X="0.3902" Y="0.9758" />
                        <FileData Type="PlistSubImage" Path="game_detail0.png" Plist="ui1.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5002" />
                    <Position X="-475.0000" Y="535.0000" />
                    <Scale ScaleX="-1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_detail1.png" Plist="ui1.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="400.0000" />
                <Scale ScaleX="0.7000" ScaleY="0.7000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2778" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="540.0000" Y="1440.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="1.0000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="86" G="92" B="124" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_view" ActionTag="-501500674" Tag="1547" IconVisible="False" LeftMargin="-1151.1091" RightMargin="1325.1091" TopMargin="319.0146" BottomMargin="770.9854" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="906.0000" Y="350.0000" />
            <AnchorPoint />
            <Position X="-1151.1091" Y="770.9854" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-1.0658" Y="0.5354" />
            <PreSize X="0.8389" Y="0.2431" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>