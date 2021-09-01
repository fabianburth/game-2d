//
// Created by burth on 26.08.2021.
//
//
//#include "GameView.h"
//
//void GameView::getGameLevelState(std::shared_ptr<GameLevel> board) {
//    for(Block block : board->Blocks){
//        for(auto const animator : blockAnimators) {
//            if(animator->block == &block){
//                if(block.state != animator->block->state)
//            }
//        }
//    }
//}
//
//GameView::GameView(std::shared_ptr<GameLevel> board) {
//    for(Block block : board->Blocks){
//        blockAnimators.emplace_back(std::make_shared<BlockAnimator>(BlockAnimator{0.5f, 3.0f,&block}));
//    }
//}
