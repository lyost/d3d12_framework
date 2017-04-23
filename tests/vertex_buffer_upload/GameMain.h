#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <vector>
#include "Game.h"
#include "Camera.h"
#include "TestGraphicsPipelinePos.h"
#include "TestGraphicsPipelinePosColor.h"
#include "TestGraphicsPipelinePosTexU.h"
#include "TestGraphicsPipelinePosTexUV.h"
#include "TestGraphicsPipelinePosTexUVW.h"
#include "TestModelPos.h"
#include "TestModelPosColor.h"
#include "TestModelPosTexU.h"
#include "TestModelPosTexUV.h"
#include "TestModelPosTexUVW.h"

class GameMain : public Game
{
  public:
    GameMain(WCHAR* title);
    ~GameMain();
    
  protected:
    /// <summary>
    /// Loads the content for the game
    /// </summary>
    void LoadContent();
    
    /// <summary>
    /// Unloads the content for the game before the dealloction of the instance
    /// </summary>
    void UnloadContent();
    
    /// <summary>
    /// Updates the game state
    /// </summary>
    /// <param name="step_ms">
    /// number of milliseconds since the last frame based on the configured frame rate
    /// </param>
    /// <param name="actual_ms">
    /// actual number of milliseconds since the last frame
    /// </param>
    void Update(UINT step_ms, UINT actual_ms);
    
    /// <summary>
    /// Draws the current frame
    /// </summary>
    /// <param name="step_ms">
    /// number of milliseconds since the last frame based on the configured frame rate
    /// </param>
    /// <param name="actual_ms">
    /// actual number of milliseconds since the last frame
    /// </param>
    void Draw(UINT step_ms, UINT actual_ms);
    
    /// <summary>
    /// Handler for when the window is resized
    /// </summary>
    /// <param name="width">
    /// width of the new client area, in pixels 
    /// </param>
    /// <param name="height">
    /// height of the new client area, in pixels
    /// </param>
    void OnResize(UINT width,UINT height);
    
  private:
    // disabled
    GameMain(const GameMain& cpy);
    GameMain& operator=(const GameMain& cpy);

    /// <summary>
    /// Helper function for creating the depth stencil on load and on resize
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void CreateDepthStencil(GraphicsCore& graphics);

    /// <summary>
    /// Updates m_camera based on m_camera_angle
    /// </summary>
    void UpdateCamera();

    /// <summary>
    /// camera for the test viewport
    /// </summary>
    Camera* m_camera;

    /// <summary>
    /// angle (in radians) of the camera orbiting the world space's origin
    /// </summary>
    float m_camera_angle;

    /// <summary>
    /// scissor rect for the full viewport
    /// </summary>
    RECT m_scissor_rect;

    /// <summary>
    /// command list to draw with
    /// </summary>
    CommandList* m_command_list;

    /// <summary>
    /// depth stencil
    /// </summary>
    DepthStencil* m_depth_stencil;

    /// <summary>
    /// graphics pipeline for the position test case
    /// </summary>
    TestGraphicsPipelinePos* m_pipeline_pos;

    /// <summary>
    /// graphics pipeline for the position and color test case
    /// </summary>
    TestGraphicsPipelinePosColor* m_pipeline_pos_color;

    /// <summary>
    /// graphics pipeline for the position and 1D texture test case
    /// </summary>
    TestGraphicsPipelinePosTexU* m_pipeline_pos_tex_u;

    /// <summary>
    /// graphics pipeline for the position and 2D texture test case
    /// </summary>
    TestGraphicsPipelinePosTexUV* m_pipeline_pos_tex_uv;

    /// <summary>
    /// graphics pipeline for the position and 3D texture test case
    /// </summary>
    TestGraphicsPipelinePosTexUVW* m_pipeline_pos_tex_uvw;

    /// <summary>
    /// model for the position test case
    /// </summary>
    TestModelPos* m_model_pos;

    /// <summary>
    /// model for the position and color test case
    /// </summary>
    TestModelPosColor* m_model_pos_color;

    /// <summary>
    /// model for the position and 1D texture test case
    /// </summary>
    TestModelPosTexU* m_model_pos_tex_u;

    /// <summary>
    /// model for the position and 2D texture test case
    /// </summary>
    TestModelPosTexUV* m_model_pos_tex_uv;

    /// <summary>
    /// model for the position and 3D texture test case
    /// </summary>
    TestModelPosTexUVW* m_model_pos_tex_uvw;
};

#endif /* GAMEMAIN_H */
