import esphome.codegen as cg
from esphome.components import climate_ir
import esphome.config_validation as cv
from esphome.types import ConfigType

from esphome.const import CONF_ID

AUTO_LOAD = ["climate_ir"]

climate_ir_electra_ns = cg.esphome_ns.namespace("climate_ir_electra")
ElectraIrClimateComponent = climate_ir_electra_ns.class_(
    "ElectraIrClimate", climate_ir.ClimateIR)

CONF_HEADER_HIGH = "header_high"
CONF_HEADER_LOW = "header_low"
CONF_BIT_HIGH = "bit_high"
CONF_BIT_ONE_LOW = "bit_one_low"
CONF_BIT_ZERO_LOW = "bit_zero_low"


CONFIG_SCHEMA = climate_ir.climate_ir_with_receiver_schema(ElectraIrClimateComponent).extend(
    {
        cv.Optional(
            CONF_HEADER_HIGH, default="9000us"
        ): cv.positive_time_period_microseconds,
        cv.Optional(
            CONF_HEADER_LOW, default="4500us"
        ): cv.positive_time_period_microseconds,
        cv.Optional(
            CONF_BIT_HIGH, default="560us"
        ): cv.positive_time_period_microseconds,
        cv.Optional(
            CONF_BIT_ONE_LOW, default="1730us"
        ): cv.positive_time_period_microseconds,
        cv.Optional(
            CONF_BIT_ZERO_LOW, default="630us"
        ): cv.positive_time_period_microseconds,
    }
)


async def to_code(config: ConfigType) -> None:
    var = await climate_ir.new_climate_ir(config)

    cg.add(var.set_header_high(config[CONF_HEADER_HIGH]))
    cg.add(var.set_header_low(config[CONF_HEADER_LOW]))
    cg.add(var.set_bit_high(config[CONF_BIT_HIGH]))
    cg.add(var.set_bit_one_low(config[CONF_BIT_ONE_LOW]))
    cg.add(var.set_bit_zero_low(config[CONF_BIT_ZERO_LOW]))
