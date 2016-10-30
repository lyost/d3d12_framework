#ifndef LOGIC_OP_H
#define LOGIC_OP_H

/// <summary>
/// Enum of the various logic ops
/// </summary>
/// <remarks>
/// Values must match D3D12_LOGIC_OP
/// </remarks>
enum LogicOp
{
  LOGIC_OP_CLEAR = 0,
  LOGIC_OP_SET,
  LOGIC_OP_COPY,
  LOGIC_OP_COPY_INVERTED,
  LOGIC_OP_NOOP,
  LOGIC_OP_INVERT,
  LOGIC_OP_AND,
  LOGIC_OP_NAND,
  LOGIC_OP_OR,
  LOGIC_OP_NOR,
  LOGIC_OP_XOR,
  LOGIC_OP_EQUIV,
  LOGIC_OP_AND_REVERSE,
  LOGIC_OP_AND_INVERTED,
  LOGIC_OP_OR_REVERSE,
  LOGIC_OP_OR_INVERTED
};

#endif /* LOGIC_OP_H */
