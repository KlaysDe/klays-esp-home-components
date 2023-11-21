import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor,sensor
from esphome.const import (
    CONF_SENSOR_ID,
    CONF_THRESHOLD,
)

CODEOWNERS = ["@kpx1"]
DEPENDENCIES = ["esp32"]

empty_text_sensor_ns = cg.esphome_ns.namespace('key_press_event_sensor')
keyboardSensorEntity = empty_text_sensor_ns.class_('KeyPressEventSensor', text_sensor.TextSensor, cg.Component)

CONFIG_SCHEMA = (text_sensor
                .text_sensor_schema(keyboardSensorEntity)
                .extend({
                })
                .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    cg.register_component(var, config)
    
    sens = await cg.get_variable(config[CONF_SENSOR_ID])
    cg.add(var.set_sensor(sens))