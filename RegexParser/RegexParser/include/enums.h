#pragma once

/// <summary>
/// Тип конструкции повтора регулярного выражения.
/// </summary>
enum class RepeatType
{
	/// <summary>
	/// Произвольное число повторений.
	/// </summary>
	Arbitrary,
	/// <summary>
	/// Ненулевое число повторений.
	/// </summary>
	NonZero,
	/// <summary>
	/// Нуль или единственное вхождение.
	/// </summary>
	NoneOrSingle
};

/// <summary>
/// Тип литерала регулярного выражения.
/// </summary>
enum class LiteralType
{
	/// <summary>
	/// Обычный символ.
	/// </summary>
	Symbol,
	/// <summary>
	/// Произвольный символ.
	/// </summary>
	Any,
	/// <summary>
	/// Пустая последовательность.
	/// </summary>
	Empty
};