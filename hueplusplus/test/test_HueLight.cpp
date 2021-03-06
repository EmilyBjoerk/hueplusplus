#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../include/Hue.h"
#include "../include/HueLight.h"
#include "../include/json/json.h"
#include "mocks/mock_HttpHandler.h"
#include "testhelper.h"

class HueLightTest : public ::testing::Test {
protected:
  std::shared_ptr<MockHttpHandler> handler;
  Json::Value hue_bridge_state;
  Hue test_bridge;

protected:
  HueLightTest()
      : handler(std::make_shared<MockHttpHandler>()),
        test_bridge(getBridgeIp(), getBridgePort(), getBridgeUsername(),
            handler) {
    using namespace ::testing;
    hue_bridge_state["lights"] = Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["1"] = Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["1"]["state"] = Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["1"]["state"]["on"] = true;
    hue_bridge_state["lights"]["1"]["state"]["bri"] = 254;
    hue_bridge_state["lights"]["1"]["state"]["ct"] = 366;
    hue_bridge_state["lights"]["1"]["state"]["alert"] = "none";
    hue_bridge_state["lights"]["1"]["state"]["colormode"] = "ct";
    hue_bridge_state["lights"]["1"]["state"]["reachable"] = true;
    hue_bridge_state["lights"]["1"]["swupdate"] =
        Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["1"]["swupdate"]["state"] = "noupdates";
    hue_bridge_state["lights"]["1"]["swupdate"]["lastinstall"] =
        Json::nullValue;
    hue_bridge_state["lights"]["1"]["type"] = "Dimmable light";
    hue_bridge_state["lights"]["1"]["name"] = "Hue lamp 1";
    hue_bridge_state["lights"]["1"]["modelid"] = "LWB004";
    hue_bridge_state["lights"]["1"]["manufacturername"] = "Philips";
    hue_bridge_state["lights"]["1"]["productname"] = "Hue bloom";
    hue_bridge_state["lights"]["1"]["uniqueid"] = "00:00:00:00:00:00:00:00-00";
    hue_bridge_state["lights"]["1"]["swversion"] = "5.50.1.19085";
    hue_bridge_state["lights"]["1"]["luminaireuniqueid"] = "0000000";
    hue_bridge_state["lights"]["2"] = Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["2"]["state"] = Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["2"]["state"]["on"] = false;
    hue_bridge_state["lights"]["2"]["state"]["bri"] = 254;
    hue_bridge_state["lights"]["2"]["state"]["ct"] = 366;
    hue_bridge_state["lights"]["2"]["state"]["hue"] = 123456;
    hue_bridge_state["lights"]["2"]["state"]["sat"] = 123;
    hue_bridge_state["lights"]["2"]["state"]["xy"][0] = 0.102;
    hue_bridge_state["lights"]["2"]["state"]["xy"][1] = 0.102;
    hue_bridge_state["lights"]["2"]["state"]["alert"] = "none";
    hue_bridge_state["lights"]["2"]["state"]["colormode"] = "ct";
    hue_bridge_state["lights"]["2"]["state"]["reachable"] = true;
    hue_bridge_state["lights"]["2"]["swupdate"] =
        Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["2"]["swupdate"]["state"] = "noupdates";
    hue_bridge_state["lights"]["2"]["swupdate"]["lastinstall"] =
        Json::nullValue;
    hue_bridge_state["lights"]["2"]["type"] = "Color light";
    hue_bridge_state["lights"]["2"]["name"] = "Hue lamp 2";
    hue_bridge_state["lights"]["2"]["modelid"] = "LST001";
    hue_bridge_state["lights"]["2"]["uniqueid"] = "11:11:11:11:11:11:11:11-11";
    hue_bridge_state["lights"]["2"]["swversion"] = "5.50.1.19085";
    hue_bridge_state["lights"]["3"] = Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["3"]["state"] = Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["3"]["state"]["on"] = false;
    hue_bridge_state["lights"]["3"]["state"]["bri"] = 254;
    hue_bridge_state["lights"]["3"]["state"]["ct"] = 366;
    hue_bridge_state["lights"]["3"]["state"]["hue"] = 123456;
    hue_bridge_state["lights"]["3"]["state"]["sat"] = 123;
    hue_bridge_state["lights"]["3"]["state"]["xy"][0] = 0.102;
    hue_bridge_state["lights"]["3"]["state"]["xy"][1] = 0.102;
    hue_bridge_state["lights"]["3"]["state"]["alert"] = "none";
    hue_bridge_state["lights"]["3"]["state"]["colormode"] = "ct";
    hue_bridge_state["lights"]["3"]["state"]["reachable"] = true;
    hue_bridge_state["lights"]["3"]["swupdate"] =
        Json::Value(Json::objectValue);
    hue_bridge_state["lights"]["3"]["swupdate"]["state"] = "noupdates";
    hue_bridge_state["lights"]["3"]["swupdate"]["lastinstall"] =
        Json::nullValue;
    hue_bridge_state["lights"]["3"]["type"] = "Color extended light";
    hue_bridge_state["lights"]["3"]["name"] = "Hue lamp 3";
    hue_bridge_state["lights"]["3"]["modelid"] = "LCT010";
    hue_bridge_state["lights"]["3"]["manufacturername"] = "Philips";
    hue_bridge_state["lights"]["3"]["productname"] = "Hue bloom";
    hue_bridge_state["lights"]["3"]["swversion"] = "5.50.1.19085";

    EXPECT_CALL(*handler,
                GETJson("/api/" + getBridgeUsername(),
                        Json::Value(Json::objectValue), getBridgeIp(), 80))
        .Times(AtLeast(1))
        .WillRepeatedly(Return(hue_bridge_state));
    EXPECT_CALL(*handler,
                GETJson("/api/" + getBridgeUsername() + "/lights/1",
                        Json::Value(Json::objectValue), getBridgeIp(), 80))
        .Times(AtLeast(1))
        .WillRepeatedly(Return(hue_bridge_state["lights"]["1"]));
    EXPECT_CALL(*handler,
                GETJson("/api/" + getBridgeUsername() + "/lights/2",
                        Json::Value(Json::objectValue), getBridgeIp(), 80))
        .Times(AtLeast(1))
        .WillRepeatedly(Return(hue_bridge_state["lights"]["2"]));
    EXPECT_CALL(*handler,
                GETJson("/api/" + getBridgeUsername() + "/lights/3",
                        Json::Value(Json::objectValue), getBridgeIp(), 80))
        .Times(AtLeast(1))
        .WillRepeatedly(Return(hue_bridge_state["lights"]["3"]));
  }
  ~HueLightTest(){};
};

TEST_F(HueLightTest, Constructor) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  HueLight test_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  HueLight test_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_3 = test_bridge.getLight(3);
}

TEST_F(HueLightTest, On) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));

  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/transitiontime"] = 255;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/3/state/on"] = true;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(true, test_light_1.On(33));
  EXPECT_EQ(false, test_light_2.On());
  EXPECT_EQ(true, test_light_3.On(255));
}

TEST_F(HueLightTest, Off) {
  using namespace ::testing;
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/1/state/transitiontime"] = 33;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/1/state/on"] = false;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/1/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(true, test_light_1.Off(33));
  EXPECT_EQ(true, test_light_2.Off());
  EXPECT_EQ(true, test_light_3.Off(255));
}

TEST_F(HueLightTest, isOn) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(true, ctest_light_1.isOn());
  EXPECT_EQ(false, ctest_light_2.isOn());
  EXPECT_EQ(false, ctest_light_3.isOn());
  EXPECT_EQ(true, test_light_1.isOn());
  EXPECT_EQ(false, test_light_2.isOn());
  EXPECT_EQ(false, test_light_3.isOn());
}

TEST_F(HueLightTest, getId) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(1, ctest_light_1.getId());
  EXPECT_EQ(2, ctest_light_2.getId());
  EXPECT_EQ(3, ctest_light_3.getId());
  EXPECT_EQ(1, test_light_1.getId());
  EXPECT_EQ(2, test_light_2.getId());
  EXPECT_EQ(3, test_light_3.getId());
}

TEST_F(HueLightTest, getType) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ("Dimmable light", ctest_light_1.getType());
  EXPECT_EQ("Color light", ctest_light_2.getType());
  EXPECT_EQ("Color extended light", ctest_light_3.getType());
  EXPECT_EQ("Dimmable light", test_light_1.getType());
  EXPECT_EQ("Color light", test_light_2.getType());
  EXPECT_EQ("Color extended light", test_light_3.getType());
}

TEST_F(HueLightTest, getName) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ("Hue lamp 1", ctest_light_1.getName());
  EXPECT_EQ("Hue lamp 2", ctest_light_2.getName());
  EXPECT_EQ("Hue lamp 3", ctest_light_3.getName());
  EXPECT_EQ("Hue lamp 1", test_light_1.getName());
  EXPECT_EQ("Hue lamp 2", test_light_2.getName());
  EXPECT_EQ("Hue lamp 3", test_light_3.getName());
}

TEST_F(HueLightTest, getModelId) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ("LWB004", ctest_light_1.getModelId());
  EXPECT_EQ("LST001", ctest_light_2.getModelId());
  EXPECT_EQ("LCT010", ctest_light_3.getModelId());
  EXPECT_EQ("LWB004", test_light_1.getModelId());
  EXPECT_EQ("LST001", test_light_2.getModelId());
  EXPECT_EQ("LCT010", test_light_3.getModelId());
}

TEST_F(HueLightTest, getUId) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ("00:00:00:00:00:00:00:00-00", ctest_light_1.getUId());
  EXPECT_EQ("11:11:11:11:11:11:11:11-11", ctest_light_2.getUId());
  EXPECT_EQ("", ctest_light_3.getUId());
  EXPECT_EQ("00:00:00:00:00:00:00:00-00", test_light_1.getUId());
  EXPECT_EQ("11:11:11:11:11:11:11:11-11", test_light_2.getUId());
  EXPECT_EQ("", test_light_3.getUId());
}

TEST_F(HueLightTest, getManufacturername) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ("Philips", ctest_light_1.getManufacturername());
  EXPECT_EQ("", ctest_light_2.getManufacturername());
  EXPECT_EQ("Philips", ctest_light_3.getManufacturername());
  EXPECT_EQ("Philips", test_light_1.getManufacturername());
  EXPECT_EQ("", test_light_2.getManufacturername());
  EXPECT_EQ("Philips", test_light_3.getManufacturername());
}

TEST_F(HueLightTest, getProductname) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ("Hue bloom", ctest_light_1.getProductname());
  EXPECT_EQ("", ctest_light_2.getProductname());
  EXPECT_EQ("Hue bloom", ctest_light_3.getProductname());
  EXPECT_EQ("Hue bloom", test_light_1.getProductname());
  EXPECT_EQ("", test_light_2.getProductname());
  EXPECT_EQ("Hue bloom", test_light_3.getProductname());
}

TEST_F(HueLightTest, getLuminaireUId) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ("0000000", ctest_light_1.getLuminaireUId());
  EXPECT_EQ("", ctest_light_2.getLuminaireUId());
  EXPECT_EQ("", ctest_light_3.getLuminaireUId());
  EXPECT_EQ("0000000", test_light_1.getLuminaireUId());
  EXPECT_EQ("", test_light_2.getLuminaireUId());
  EXPECT_EQ("", test_light_3.getLuminaireUId());
}

TEST_F(HueLightTest, getSwVersion) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ("5.50.1.19085", ctest_light_1.getSwVersion());
  EXPECT_EQ("5.50.1.19085", ctest_light_2.getSwVersion());
  EXPECT_EQ("5.50.1.19085", ctest_light_3.getSwVersion());
  EXPECT_EQ("5.50.1.19085", test_light_1.getSwVersion());
  EXPECT_EQ("5.50.1.19085", test_light_2.getSwVersion());
  EXPECT_EQ("5.50.1.19085", test_light_3.getSwVersion());
}

TEST_F(HueLightTest, setName) {
  using namespace ::testing;
  Json::Value expected_request(Json::objectValue);
  expected_request["name"] = "Baskj189";
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/1/name"] =
      expected_request["name"].asString();
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/1/name",
                      expected_request, getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/name",
                      expected_request, getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/name"] =
      expected_request["name"].asString();
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/name",
                      expected_request, getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(true, test_light_1.setName(expected_request["name"].asString()));
  EXPECT_EQ(false, test_light_2.setName(expected_request["name"].asString()));
  EXPECT_EQ(true, test_light_3.setName(expected_request["name"].asString()));
}

TEST_F(HueLightTest, getColorType) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(ColorType::NONE, ctest_light_1.getColorType());
  EXPECT_EQ(ColorType::GAMUT_A, ctest_light_2.getColorType());
  EXPECT_EQ(ColorType::GAMUT_C, ctest_light_3.getColorType());
  EXPECT_EQ(ColorType::NONE, test_light_1.getColorType());
  EXPECT_EQ(ColorType::GAMUT_A, test_light_2.getColorType());
  EXPECT_EQ(ColorType::GAMUT_C, test_light_3.getColorType());
}

TEST_F(HueLightTest, KelvinToMired) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(10000, ctest_light_1.KelvinToMired(100));
  EXPECT_EQ(500, ctest_light_2.KelvinToMired(2000));
  EXPECT_EQ(303, ctest_light_3.KelvinToMired(3300));
  EXPECT_EQ(250, test_light_1.KelvinToMired(4000));
  EXPECT_EQ(200, test_light_2.KelvinToMired(5000));
  EXPECT_EQ(166, test_light_3.KelvinToMired(6000));
}

TEST_F(HueLightTest, MiredToKelvin) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(100, ctest_light_1.MiredToKelvin(10000));
  EXPECT_EQ(2000, ctest_light_2.MiredToKelvin(500));
  EXPECT_EQ(3300, ctest_light_3.MiredToKelvin(303));
  EXPECT_EQ(4000, test_light_1.MiredToKelvin(250));
  EXPECT_EQ(5000, test_light_2.MiredToKelvin(200));
  EXPECT_EQ(6024, test_light_3.MiredToKelvin(
                      166)); // 6000 kelvin should be 166 mired, but keep in
                             // mind flops are not exact
}

TEST_F(HueLightTest, hasBrightnessControl) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(true, ctest_light_1.hasBrightnessControl());
  EXPECT_EQ(true, ctest_light_2.hasBrightnessControl());
  EXPECT_EQ(true, ctest_light_3.hasBrightnessControl());
  EXPECT_EQ(true, test_light_1.hasBrightnessControl());
  EXPECT_EQ(true, test_light_2.hasBrightnessControl());
  EXPECT_EQ(true, test_light_3.hasBrightnessControl());
}

TEST_F(HueLightTest, hasTemperatureControl) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, ctest_light_1.hasTemperatureControl());
  EXPECT_EQ(false, ctest_light_2.hasTemperatureControl());
  EXPECT_EQ(true, ctest_light_3.hasTemperatureControl());
  EXPECT_EQ(false, test_light_1.hasTemperatureControl());
  EXPECT_EQ(false, test_light_2.hasTemperatureControl());
  EXPECT_EQ(true, test_light_3.hasTemperatureControl());
}

TEST_F(HueLightTest, hasColorControl) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, ctest_light_1.hasColorControl());
  EXPECT_EQ(true, ctest_light_2.hasColorControl());
  EXPECT_EQ(true, ctest_light_3.hasColorControl());
  EXPECT_EQ(false, test_light_1.hasColorControl());
  EXPECT_EQ(true, test_light_2.hasColorControl());
  EXPECT_EQ(true, test_light_3.hasColorControl());
}

TEST_F(HueLightTest, setBrightness) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/1/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/transitiontime"] = 0;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/3/state/on"] = true;
  prep_ret[2] = Json::Value(Json::objectValue);
  prep_ret[2]["success"] = Json::Value(Json::objectValue);
  prep_ret[2]["success"]["/lights/3/state/bri"] = 254;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.setBrightness(200));
  EXPECT_EQ(true, test_light_2.setBrightness(0, 2));
  EXPECT_EQ(true, test_light_3.setBrightness(255, 0));
}

TEST_F(HueLightTest, getBrightness) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(254, ctest_light_1.getBrightness());
  EXPECT_EQ(254, ctest_light_2.getBrightness());
  EXPECT_EQ(254, ctest_light_3.getBrightness());
  EXPECT_EQ(254, test_light_1.getBrightness());
  EXPECT_EQ(254, test_light_2.getBrightness());
  EXPECT_EQ(254, test_light_3.getBrightness());
}

TEST_F(HueLightTest, setColorTemperature) {
  using namespace ::testing;
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[2] = Json::Value(Json::objectValue);
  prep_ret[2]["success"] = Json::Value(Json::objectValue);
  prep_ret[2]["success"]["/lights/3/state/ct"] = 153;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/3/state/on"] = true;
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/transitiontime"] = 0;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.setColorTemperature(153));
  EXPECT_EQ(false, test_light_2.setColorTemperature(400, 2));
  EXPECT_EQ(true, test_light_3.setColorTemperature(100, 0));
}

TEST_F(HueLightTest, getColorTemperature) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(0, ctest_light_1.getColorTemperature());
  EXPECT_EQ(0, ctest_light_2.getColorTemperature());
  EXPECT_EQ(366, ctest_light_3.getColorTemperature());
  EXPECT_EQ(0, test_light_1.getColorTemperature());
  EXPECT_EQ(0, test_light_2.getColorTemperature());
  EXPECT_EQ(366, test_light_3.getColorTemperature());
}

TEST_F(HueLightTest, setColorHue) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[2] = Json::Value(Json::objectValue);
  prep_ret[2]["success"] = Json::Value(Json::objectValue);
  prep_ret[2]["success"]["/lights/3/state/hue"] = 65500;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/3/state/on"] = true;
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/transitiontime"] = 0;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.setColorHue(153));
  EXPECT_EQ(false, test_light_2.setColorHue(30000, 2));
  EXPECT_EQ(true, test_light_3.setColorHue(65500, 0));
}

TEST_F(HueLightTest, setColorSaturation) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[2] = Json::Value(Json::objectValue);
  prep_ret[2]["success"] = Json::Value(Json::objectValue);
  prep_ret[2]["success"]["/lights/3/state/sat"] = 250;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/3/state/on"] = true;
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/transitiontime"] = 0;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.setColorSaturation(0));
  EXPECT_EQ(false, test_light_2.setColorSaturation(140, 2));
  EXPECT_EQ(true, test_light_3.setColorSaturation(250, 0));
}

TEST_F(HueLightTest, setColorHueSaturation) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[3] = Json::Value(Json::objectValue);
  prep_ret[3]["success"] = Json::Value(Json::objectValue);
  prep_ret[3]["success"]["/lights/3/state/sat"] = 250;
  prep_ret[2] = Json::Value(Json::objectValue);
  prep_ret[2]["success"] = Json::Value(Json::objectValue);
  prep_ret[2]["success"]["/lights/3/state/hue"] = 65500;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/3/state/on"] = true;
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/transitiontime"] = 0;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.setColorHueSaturation(153, 0));
  EXPECT_EQ(false, test_light_2.setColorHueSaturation(30000, 140, 2));
  EXPECT_EQ(true, test_light_3.setColorHueSaturation(65500, 250, 0));
}

TEST_F(HueLightTest, getColorHueSaturation) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(std::make_pair(static_cast<uint16_t>(0), static_cast<uint8_t>(0)),
            ctest_light_1.getColorHueSaturation());
  EXPECT_EQ(
      std::make_pair(static_cast<uint16_t>(123456), static_cast<uint8_t>(123)),
      ctest_light_2.getColorHueSaturation());
  EXPECT_EQ(
      std::make_pair(static_cast<uint16_t>(123456), static_cast<uint8_t>(123)),
      ctest_light_3.getColorHueSaturation());
  EXPECT_EQ(std::make_pair(static_cast<uint16_t>(0), static_cast<uint8_t>(0)),
            test_light_1.getColorHueSaturation());
  EXPECT_EQ(
      std::make_pair(static_cast<uint16_t>(123456), static_cast<uint8_t>(123)),
      test_light_2.getColorHueSaturation());
  EXPECT_EQ(
      std::make_pair(static_cast<uint16_t>(123456), static_cast<uint8_t>(123)),
      test_light_3.getColorHueSaturation());
}

TEST_F(HueLightTest, setColorXY) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[2] = Json::Value(Json::objectValue);
  prep_ret[2]["success"] = Json::Value(Json::objectValue);
  prep_ret[2]["success"]["/lights/3/state/xy"][0] = 0.4232;
  prep_ret[2]["success"]["/lights/3/state/xy"][1] = 0.1231;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/3/state/on"] = true;
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/transitiontime"] = 0;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.setColorXY(0.01, 0));
  EXPECT_EQ(false, test_light_2.setColorXY(0.123, 1, 2));
  EXPECT_EQ(true, test_light_3.setColorXY(0.4232, 0.1231, 0));
}

TEST_F(HueLightTest, getColorXY) {
  const HueLight ctest_light_1 = test_bridge.getLight(1);
  const HueLight ctest_light_2 = test_bridge.getLight(2);
  const HueLight ctest_light_3 = test_bridge.getLight(3);
  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(std::make_pair(static_cast<float>(0), static_cast<float>(0)),
            ctest_light_1.getColorXY());
  EXPECT_EQ(
      std::make_pair(static_cast<float>(0.102), static_cast<float>(0.102)),
      ctest_light_2.getColorXY());
  EXPECT_EQ(
      std::make_pair(static_cast<float>(0.102), static_cast<float>(0.102)),
      ctest_light_3.getColorXY());
  EXPECT_EQ(std::make_pair(static_cast<float>(0), static_cast<float>(0)),
            test_light_1.getColorXY());
  EXPECT_EQ(
      std::make_pair(static_cast<float>(0.102), static_cast<float>(0.102)),
      test_light_2.getColorXY());
  EXPECT_EQ(
      std::make_pair(static_cast<float>(0.102), static_cast<float>(0.102)),
      test_light_3.getColorXY());
}

TEST_F(HueLightTest, setColorRGB) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[2] = Json::Value(Json::objectValue);
  prep_ret[2]["success"] = Json::Value(Json::objectValue);
  prep_ret[2]["success"]["/lights/3/state/xy"][0] = 0.1596;
  prep_ret[2]["success"]["/lights/3/state/xy"][1] = 0.1437;
  prep_ret[1] = Json::Value(Json::objectValue);
  prep_ret[1]["success"] = Json::Value(Json::objectValue);
  prep_ret[1]["success"]["/lights/3/state/on"] = true;
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/transitiontime"] = 0;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.setColorRGB(0, 0, 0, 0));
  EXPECT_EQ(false, test_light_2.setColorRGB(32, 64, 128, 2));
  EXPECT_EQ(true, test_light_3.setColorRGB(64, 128, 255, 0));
}

TEST_F(HueLightTest, alert) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/1/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  Json::Value prep_ret;
  prep_ret = Json::Value(Json::arrayValue);
  prep_ret[0] = Json::Value(Json::objectValue);
  prep_ret[0]["success"] = Json::Value(Json::objectValue);
  prep_ret[0]["success"]["/lights/3/state/alert"] = "select";
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(prep_ret));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.alert());
  EXPECT_EQ(false, test_light_2.alert());
  EXPECT_EQ(true, test_light_3.alert());
}

TEST_F(HueLightTest, alertTemperature) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.alertTemperature(400));
  EXPECT_EQ(false, test_light_2.alertTemperature(100));
  EXPECT_EQ(false, test_light_3.alertTemperature(0));
}

TEST_F(HueLightTest, alertHueSaturation) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.alertHueSaturation(0, 255));
  EXPECT_EQ(false, test_light_2.alertHueSaturation(3000, 100));
  EXPECT_EQ(false, test_light_3.alertHueSaturation(50000, 0));
}

TEST_F(HueLightTest, alertXY) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.alertXY(0.1, 0.1));
  EXPECT_EQ(false, test_light_2.alertXY(0.2434, 0.2344));
  EXPECT_EQ(false, test_light_3.alertXY(0.1234, 0.1234));
}

TEST_F(HueLightTest, alertRGB) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.alertRGB(0, 0, 0));
  EXPECT_EQ(false, test_light_2.alertRGB(32, 64, 128));
  EXPECT_EQ(false, test_light_3.alertRGB(64, 128, 255));
}

TEST_F(HueLightTest, setColorLoop) {
  using namespace ::testing;
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/2/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));
  EXPECT_CALL(*handler,
              PUTJson("/api/" + getBridgeUsername() + "/lights/3/state", _,
                      getBridgeIp(), 80))
      .Times(1)
      .WillOnce(Return(Json::Value(Json::arrayValue)));

  HueLight test_light_1 = test_bridge.getLight(1);
  HueLight test_light_2 = test_bridge.getLight(2);
  HueLight test_light_3 = test_bridge.getLight(3);

  EXPECT_EQ(false, test_light_1.setColorLoop(true));
  EXPECT_EQ(false, test_light_2.setColorLoop(false));
  EXPECT_EQ(false, test_light_3.setColorLoop(true));
}

TEST_F(HueLightTest, refreshState) {
  using namespace ::testing;
  test_bridge.getLight(1);
  test_bridge.getLight(2);
  test_bridge.getLight(3);

  EXPECT_CALL(*handler,
              GETJson("/api/" + getBridgeUsername() + "/lights/1",
                      Json::Value(Json::objectValue), getBridgeIp(), 80))
      .Times(2)
      .WillRepeatedly(Return(Json::Value(Json::objectValue)));

  const HueLight ctest_light_1 = test_bridge.getLight(1);
  HueLight test_light_1 = test_bridge.getLight(1);
}
