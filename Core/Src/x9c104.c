#include "main.h"

void X9C104_INIT(size_t *step)
{
  size_t i;
  // Set step to zero
  step = 0;
  // Pull up INC 
  HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_SET);
  HAL_Delay(10);
  // Pull down CS to activate resistor change
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  // Reduce resistor value
  HAL_GPIO_WritePin(U_D_GPIO_Port, U_D_Pin, GPIO_PIN_SET);
  // Return to zero
  for(i = 0; i < 100; i++){
    // Pull up INC
    HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_SET);
    HAL_Delay(10);
    // Pull down INC
    HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_RESET);
  }
  // Initiliaize finshed, start saving
  HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_SET);
  HAL_Delay(10);
  // Disable changing
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

void X9C104_CHANGE_Step(size_t *current_step, size_t change_to_step)
{
    // Enable Changing
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    // If current step is less than change_to step, increasing resistor value
    if(*current_step < change_to_step){
        // Increasing resistor mode
        HAL_GPIO_WritePin(U_D_GPIO_Port, U_D_Pin, GPIO_PIN_RESET);
        HAL_Delay(10);
        // Start moving to the step setting up
        for(; *current_step != change_to_step; ++(*current_step)){
            HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_SET);
            HAL_Delay(100);
            HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_RESET);

        }
    } else {
        // If current step is greater than change_to_step, decreasing resistor value
        HAL_GPIO_WritePin(U_D_GPIO_Port, U_D_Pin, GPIO_PIN_SET);
        HAL_Delay(10);
        for(; *current_step != change_to_step; --(*current_step)){
            HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_SET);
            HAL_Delay(100);
            HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_RESET);
        }
    // Changing finshed, start saving
    HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, GPIO_PIN_SET);
    // Disable changing
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
    }
}