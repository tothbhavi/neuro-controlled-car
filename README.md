# 🧠 Neuro-Controlled Car (Eye-Blink BCI)

> A brain-computer interface car controlled entirely by **eye blinks** — no joystick, no hands, no remote.

---

## 🎯 What This Does

This system reads **EOG (Electrooculography) signals** from electrodes placed around the eyes, detects blinks in real time, and wirelessly commands a car to move — all using bioelectric signals from the human body.

- 👁️ **Single blink** → Car moves **Forward**
- 👁️👁️ **Double blink** → Car moves **Backward**
- ⏱️ Auto-stop after 5 seconds for safety

---

## 🔧 System Architecture

```
Electrodes (Eyes) → BioAmp EXG Pill → Arduino Nano (Transmitter)
                                              ↓
                                        nRF24L01 (Wireless)
                                              ↓
                                    Arduino UNO (Receiver)
                                              ↓
                                    L298N Motor Driver → DC Motors
```

---

## 🧩 Components

### Transmitter (Neuro Side)
| Component | Purpose |
|-----------|---------|
| Arduino Nano/Minima | Main microcontroller |
| BioAmp EXG Pill | Biomedical signal acquisition |
| Ag/AgCl Electrodes | EOG signal capture from eyes |
| nRF24L01 + antenna | Wireless transmission |

### Receiver (Car Side)
| Component | Purpose |
|-----------|---------|
| Arduino UNO | Main microcontroller |
| nRF24L01 + antenna | Wireless reception |
| L298N Motor Driver | Dual DC motor control |
| 2x DC Motors | Left and right drive |
| 3x Li-ion Batteries | Power supply |

---

## ⚡ Signal Processing Pipeline

1. **Raw EOG signal** captured via Ag/AgCl electrodes
2. **DC offset removal** — centers signal around zero
3. **Exponential Moving Average** filter (α = 0.3) for smoothing
4. **Spike detection** — computes delta between filtered samples
5. **Blink classification** — threshold + 400ms debounce timer
6. **Command encoding** — 'F' (forward) or 'B' (backward) sent via nRF24L01

---

## 📡 Wiring

### nRF24L01 (Both Arduinos)
| nRF24L01 Pin | Arduino Pin |
|-------------|-------------|
| VCC | 3.3V (NOT 5V) |
| GND | GND |
| CE | D9 |
| CSN | D10 |
| SCK | D13 |
| MOSI | D11 |
| MISO | D12 |

> ⚠️ Add 10µF capacitor between VCC and GND on nRF24L01 — prevents unstable communication

### L298N Motor Driver
| L298N Pin | Arduino Pin |
|-----------|-------------|
| ENA | D5 (PWM) |
| ENB | D6 (PWM) |
| IN1 | D8 |
| IN2 | D7 |
| IN3 | D4 |
| IN4 | D3 |

---

## 💻 Code

See the source files in this repository:
- [`transmitter.ino`](transmitter.ino) — Neuro side (signal acquisition + wireless TX)
- [`receiver.ino`](receiver.ino) — Car side (wireless RX + motor control)

---

## 🚀 How to Run

1. Install libraries: `RF24` by TMRh20 via Arduino Library Manager
2. Upload `transmitter.ino` to Arduino Nano
3. Upload `receiver.ino` to Arduino UNO
4. Place electrodes: left eye → Electrode 1, right eye → Electrode 2, forehead → GND reference
5. Clean skin before placing electrodes for better signal
6. Power up both Arduinos and blink to control the car

---

## 👤 Author

**Paluvad Tothbhavi** — ECE (VLSI) @ GITAM Hyderabad  
📧 tpaluvad@student.gitam.edu  
🔗 [GitHub](https://github.com/tothbhavi)

---

*Built in 1st year. Real hardware. Real signals.*
