// --------------------------------------------------------------------------
// Algorithm init
//
// Data default
// --------------------------------------------------------------------------

{string} products = ...;
{string} machines = ...;
{int} time_periods = ...;
{int} first_m=...;
{int} other_m=...;
{int} last_m=...;

float profit_contribution[products] = ...;
float time_table[machines][products] = ...;
float qMachine[machines] = ...;
float upper[time_periods][products] = ...;
int repair_test[time_periods][machines]=...;

float storeCost = ...;
float storeCapacity = ...;
float endStock = ...;
float hoursPerMonth = ...;


dvar float+ manu[time_periods][products];
dvar float+ held[time_periods][products];
dvar float+ sell[time_periods][products];
dvar int+ repair[time_periods][machines];

maximize
  sum( r in time_periods)
    sum( p in products ) 
      ( sell[r][p]*profit_contribution[p] - storeCost * held[r][p] );
   
subject to {

  forall(p in products)
    ctHold_init:
     manu[1][p] == sell[1][p] + held[1][p];

  forall(p in products)
      forall(r in other_m)
        ctHold_other:
          manu[r][p]+held[r-1][p] == sell[r][p] + held[r][p];
  
  forall(r in time_periods)
    forall(m in machines)
      repair[r][m] <= qMachine[m];
     
  forall(m in machines)
    sum(r in time_periods)
      repair[r][m] == qMachine[m];
      
  forall(t in time_periods)
    forall(p in products)
      held[t][p] <= storeCapacity;
      
  forall(t in time_periods)
    forall(p in products)
      sell[t][p] <= upper[t][p];
      
  forall(t in time_periods)
    forall(m in machines)
      sum(p in products)
        time_table[m][p]*manu[t][p] <= hoursPerMonth * (qMachine[m]-repair[t][m]);
    
  forall(r in last_m)
    forall(p in products)
      held[r][p] == endStock;


}
