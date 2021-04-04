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
	NoneOrSingle,
	/// <summary>
	/// Заданный диапазон числа вхождений.
	/// </summary>
	Range
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

/// <summary>
/// Тип перехода в КА.
/// </summary>
enum class ArcType
{
	/// <summary>
	/// Символьный переход.
	/// </summary>
	Symbol,
	/// <summary>
	/// Лямбда-переход.
	/// </summary>
	Lambda
};

/// <summary>
/// Тип перехода, осуществленного КА.
/// </summary>
enum class TransitionType
{
	/// <summary>
	/// Успешныый переход в новое состояние.
	/// </summary>
	Successful,
	/// <summary>
	/// Невозможно совершить переход.
	/// </summary>
	Impossible,
	/// <summary>
	/// Лямбда-переход в новое состояние.
	/// </summary>
	Lambda
};