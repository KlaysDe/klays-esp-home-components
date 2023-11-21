import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID

CODEOWNERS = ["@kpx1"]
DEPENDENCIES = ["esp32"]

empty_text_sensor_ns = cg.esphome_ns.namespace('key_press_event_sensor')
EmptyTextSensor = empty_text_sensor_ns.class_('KeyPressEventSensor', text_sensor.TextSensor, cg.Component)

CONFIG_SCHEMA = text_sensor.TEXT_SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(EmptyTextSensor)
}).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield text_sensor.register_text_sensor(var, config)
    yield cg.register_component(var, config)