# 🧠 Global Neural Weight Catalog: Emotion Engine v4.0.2

This catalog provides a curated list of **40 high-fidelity, local-first LLMs**. These models are verified for auto-discovery by the **Emotion Engine**.

---

## ⚡ Tier 1: Ultra-Lightweight (1B - 4B Params)
*Best for: Laptops, Mobile Workstations, and older CPUs. Requires < 4GB VRAM.*

| Model Name | Param Count | Hugging Face (GGUF) | Ollama Command |
| :--- | :--- | :--- | :--- |
| **Qwen2-1.5B** | 1.5B | [Download](https://huggingface.co/Qwen/Qwen2-1.5B-Instruct-GGUF/resolve/main/qwen2-1_5b-instruct-q4_k_m.gguf) | `ollama run qwen2:1.5b` |
| **Gemma-2B-it** | 2B | [Download](https://huggingface.co/google/gemma-2b-it-GGUF/resolve/main/gemma-2b-it.gguf) | `ollama run gemma:2b` |
| **Phi-3-Mini** | 3.8B | [Download](https://huggingface.co/microsoft/Phi-3-mini-4k-instruct-gguf/resolve/main/Phi-3-mini-4k-instruct-q4.gguf) | `ollama run phi3:mini` |
| **StableLM-Zephyr** | 3B | [Download](https://huggingface.co/TheBloke/stablelm-zephyr-3b-GGUF/resolve/main/stablelm-zephyr-3b.Q4_K_M.gguf) | `ollama run stablelm-zephyr` |
| **TinyLlama-1.1B** | 1.1B | [Download](https://huggingface.co/TheBloke/TinyLlama-1.1B-Chat-v1.0-GGUF/resolve/main/tinyllama-1.1b-chat-v1.0.Q4_K_M.gguf) | `ollama run tinyllama` |
| **Phi-2** | 2.7B | [Download](https://huggingface.co/TheBloke/phi-2-GGUF/resolve/main/phi-2.Q4_K_M.gguf) | `ollama run phi` |
| **MiniCPM-2B** | 2.4B | [Download](https://huggingface.co/openbmb/MiniCPM-2B-sft-fp32-GGUF/resolve/main/MiniCPM-2B-sft-fp32.gguf) | `ollama run minicpm` |
| **Rocket-3B** | 3B | [Download](https://huggingface.co/TheBloke/rocket-3B-GGUF/resolve/main/rocket-3b.Q4_K_M.gguf) | `ollama run rocket-3b` |
| **OpenELM-1.1B** | 1.1B | [Download](https://huggingface.co/apple/OpenELM-1.1B-Instruct/resolve/main/openelm-1_1b-instruct.gguf) | `ollama run openelm` |
| **Falcon-RW-1B** | 1B | [Download](https://huggingface.co/TheBloke/falcon-rw-1b-GGUF/resolve/main/falcon-rw-1b.Q4_K_M.gguf) | `ollama run falcon:1b` |

---

## 💎 Tier 2: Standard Workstations (7B - 9B Params)
*The "Sweet Spot" for AI training. Requires 8GB - 12GB VRAM.*

| Model Name | Param Count | Hugging Face (GGUF) | Ollama Command |
| :--- | :--- | :--- | :--- |
| **Llama-3-8B** | 8B | [Download](https://huggingface.co/MaziyarPanahi/Llama-3-8B-Instruct-v0.3-GGUF/resolve/main/Llama-3-8B-Instruct-v0.3.Q4_K_M.gguf) | `ollama run llama3` |
| **Mistral-7B-v0.3** | 7B | [Download](https://huggingface.co/maziyarpanahi/Mistral-7B-Instruct-v0.3-GGUF/resolve/main/Mistral-7B-Instruct-v0.3.Q4_K_M.gguf) | `ollama run mistral` |
| **Gemma-2-9B** | 9B | [Download](https://huggingface.co/bartowski/gemma-2-9b-it-GGUF/resolve/main/gemma-2-9b-it-Q4_K_M.gguf) | `ollama run gemma2` |
| **Nous Hermes 2** | 8B | [Download](https://huggingface.co/NousResearch/Hermes-2-Pro-Llama-3-8B-GGUF/resolve/main/Hermes-2-Pro-Llama-3-8B.Q4_K_M.gguf) | `ollama run nous-hermes2` |
| **OpenChat 3.5** | 7B | [Download](https://huggingface.co/TheBloke/openchat_3.5-GGUF/resolve/main/openchat_3.5.Q4_K_M.gguf) | `ollama run openchat` |
| **Starling-LM-7B** | 7B | [Download](https://huggingface.co/TheBloke/Starling-LM-7B-alpha-GGUF/resolve/main/starling-lm-7b-alpha.Q4_K_M.gguf) | `ollama run starling-lm` |
| **Zephyr-7B-Beta** | 7B | [Download](https://huggingface.co/TheBloke/zephyr-7B-beta-GGUF/resolve/main/zephyr-7b-beta.Q4_K_M.gguf) | `ollama run zephyr` |
| **Neural-Chat-7B** | 7B | [Download](https://huggingface.co/TheBloke/neural-chat-7b-v3-1-GGUF/resolve/main/neural-chat-7b-v3-1.Q4_K_M.gguf) | `ollama run neural-chat` |
| **DeepSeek-Math** | 7B | [Download](https://huggingface.co/mradermacher/deepseek-math-7b-instruct-GGUF/resolve/main/deepseek-math-7b-instruct.Q4_K_M.gguf) | `ollama run deepseek-math` |
| **Dolphin-Mistral** | 7B | [Download](https://huggingface.co/TheBloke/dolphin-2.2.1-mistral-7B-GGUF/resolve/main/dolphin-2.2.1-mistral-7b.Q4_K_M.gguf) | `ollama run dolphin-mistral` |

---

## 🚀 Tier 3: Pro-Grade / MoE (10B - 35B Params)
*Best for: RTX 3080/4080 (16GB VRAM). High complexity reasoning.*

| Model Name | Param Count | Hugging Face (GGUF) | Ollama Command |
| :--- | :--- | :--- | :--- |
| **Qwen2-14B** | 14B | [Download](https://huggingface.co/Qwen/Qwen2-14B-Instruct-GGUF/resolve/main/qwen2-14b-instruct-q4_k_m.gguf) | `ollama run qwen2:14b` |
| **Command R** | 35B | [Download](https://huggingface.co/andrewcanis/c4ai-command-r-v01-GGUF/resolve/main/c4ai-command-r-v01-Q4_K_M.gguf) | `ollama run command-r` |
| **StarCoder2-15B** | 15B | [Download](https://huggingface.co/mradermacher/starcoder2-15b-GGUF/resolve/main/starcoder2-15b.Q4_K_M.gguf) | `ollama run starcoder2:15b` |
| **DeepSeek-V2-Lite** | 16B | [Download](https://huggingface.co/mradermacher/DeepSeek-V2-Lite-Chat-GGUF/resolve/main/DeepSeek-V2-Lite-Chat.Q4_K_M.gguf) | `ollama run deepseek-v2` |
| **Solar-10.7B** | 10.7B | [Download](https://huggingface.co/TheBloke/SOLAR-10.7B-Instruct-v1.0-GGUF/resolve/main/solar-10.7b-instruct-v1.0.Q4_K_M.gguf) | `ollama run solar` |
| **Mistral-NeMo** | 12B | [Download](https://huggingface.co/bartowski/Mistral-Nemo-Instruct-2407-GGUF/resolve/main/Mistral-Nemo-Instruct-2407-Q4_K_M.gguf) | `ollama run mistral-nemo` |
| **InternLM2-20B** | 20B | [Download](https://huggingface.co/internlm/internlm2-chat-20b-gguf/resolve/main/internlm2-chat-20b.gguf) | `ollama run internlm2:20b` |
| **Codestral-22B** | 22B | [Download](https://huggingface.co/bartowski/Codestral-22B-v0.1-GGUF/resolve/main/Codestral-22B-v0.1-Q4_K_M.gguf) | `ollama run codestral` |
| **Yi-1.5-34B** | 34B | [Download](https://huggingface.co/mradermacher/Yi-1.5-34B-Chat-GGUF/resolve/main/Yi-1.5-34B-Chat.Q4_K_M.gguf) | `ollama run yi:34b` |
| **Aya-23-35B** | 35B | [Download](https://huggingface.co/MaziyarPanahi/Aya-23-35B-GGUF/resolve/main/Aya-23-35B.Q4_K_M.gguf) | `ollama run aya:35b` |

---

## 🏛️ Tier 4: Research Titans (46B - 314B Params)
*The Pinnacle. Requires Dual-GPUs or Mac Studio. Total immersion.*

| Model Name | Param Count | Hugging Face (GGUF) | Ollama Command |
| :--- | :--- | :--- | :--- |
| **Llama-3-70B** | 70B | [Download](https://huggingface.co/MaziyarPanahi/Meta-Llama-3-70B-Instruct-GGUF/resolve/main/Meta-Llama-3-70B-Instruct.Q4_K_M.gguf) | `ollama run llama3:70b` |
| **Qwen2-72B** | 72B | [Download](https://huggingface.co/Qwen/Qwen2-72B-Instruct-GGUF/resolve/main/qwen2-72b-instruct-q4_k_m.gguf) | `ollama run qwen2:72b` |
| **Mixtral-8x22B** | 141B | [Download](https://huggingface.co/maziyarpanahi/Mixtral-8x22B-v0.1-GGUF/resolve/main/Mixtral-8x22B-v0.1.Q4_K_M.gguf) | `ollama run mixtral:8x22b` |
| **Grok-1** | 314B | [Search GGUF](https://huggingface.co/models?search=grok-1-gguf) | `ollama run grok` |
| **DBRX-Instruct** | 132B | [Download](https://huggingface.co/mradermacher/dbrx-instruct-GGUF/resolve/main/dbrx-instruct.Q4_K_M.gguf) | `ollama run dbrx` |
| **Mixtral-8x7B** | 46B | [Download](https://huggingface.co/TheBloke/Mixtral-8x7B-v0.1-GGUF/resolve/main/mixtral-8x7b-v0.1.Q4_K_M.gguf) | `ollama run mixtral` |
| **DeepSeek-V2** | 236B | [Download](https://huggingface.co/mradermacher/DeepSeek-V2-GGUF/resolve/main/DeepSeek-V2.Q4_K_M.gguf) | `ollama run deepseek-v2:236b` |
| **Command R+** | 104B | [Download](https://huggingface.co/pmysl/c4ai-command-r-plus-GGUF/resolve/main/c4ai-command-r-plus-Q4_K_M.gguf) | `ollama run command-r-plus` |
| **Falcon-180B** | 180B | [Search GGUF](https://huggingface.co/models?search=falcon-180b-gguf) | `ollama run falcon:180b` |
| **Xwin-LM-70B** | 70B | [Download](https://huggingface.co/TheBloke/Xwin-LM-70B-V0.1-GGUF/resolve/main/xwin-lm-70b-v0.1.Q4_K_M.gguf) | `ollama run xwin-lm:70b` |

---

## 🛠️ Auto-Discovery & Global Search
The **Emotion Engine** scans the following paths automatically for these models:
- **Linux**: `~/.ollama/models`, `~/.cache/lm-studio/models`, `~/Downloads`
- **Windows**: `%USERPROFILE%\.ollama\models`, `Downloads`
- **Mac**: `~/.ollama/models`, `~/Library/Application Support/lm-studio`, `Downloads`
